/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/16 07:25:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <rt/render/backend/raytracer.h>

void	rt_backend_raytracer_cylinder_twod_relative_point(
	t_vec3d *relative_coo,
	const t_ray *ray,
	const t_cylinder *c_cy
) {
	const t_vec3d	hit = v3d_sub(&ray->hit_point, &c_cy->center);
	const double	b = v3d_dot(&hit, &c_cy->axis);
	const t_vec3d	a = v3d_addmult(&c_cy->center, &c_cy->axis, b);
	const t_vec3d	sol = m3d_solv(m3d(c_cy->vec_udir, c_cy->vec_vdir,
				c_cy->axis), v3d_sub(&ray->hit_point, &a));

	relative_coo->x = b;
	relative_coo->y = ft_fsign(sol.y) * \
		acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));
	relative_coo->z = v3d_lensub(&a, &ray->hit_point) - c_cy->diameter / 2;
}

void	rt_backend_raytracer_cylinder(t_obj *obj)
{
	t_cylinder	*cy;
	t_vec3d		tmp;
	t_vec3d		tmp2;
	t_vec3d		high;

	cy = (t_cylinder *)obj;
	tmp = v3d(cy->axis.y + cy->axis.z, -cy->axis.x, -cy->axis.x);
	cy->vec_udir = v3d_norm(&tmp);
	tmp = v3d_cross(&cy->axis, &cy->vec_udir);
	cy->vec_vdir = v3d_norm(&tmp);
	cy->sq_radius = cy->diameter * cy->diameter / 4;
	cy->top_center = v3d_addmult(&cy->center, &cy->axis, cy->height);
	tmp = rt_backend_raytracer_highest_point_circle(cy->vec_udir,
			cy->vec_vdir, cy->center, cy->diameter / 2);
	tmp2 = rt_backend_raytracer_highest_point_circle(cy->vec_udir,
			cy->vec_vdir, cy->top_center, cy->diameter / 2);
	high = v3d_max(&tmp, &tmp2);
	tmp = rt_backend_raytracer_lowest_point_circle(cy->vec_udir,
			cy->vec_vdir, cy->center, cy->diameter / 2);
	tmp2 = rt_backend_raytracer_lowest_point_circle(cy->vec_udir,
			cy->vec_vdir, cy->top_center, cy->diameter / 2);
	rt_backend_raytracer_creating_aabbx(&cy->aabbx, high, v3d_min(&tmp, &tmp2));
	obj->intersect = rt_backend_raytracer_cylinder_intersection;
	obj->calc_normal = rt_backend_raytracer_cylinder_normal;
	obj->calc_color = rt_backend_raytracer_colors_cylinder;
}

// t_obj	*cylinder(t_vec3d coo, t_vec3d vector,
// double height, double diam, t_vec3d colors)
// {
// 	t_obj		*new;
// 	t_cylinder	*cy;
//
// 	cy = rt_malloc_aligned(sizeof(t_cylinder), 32);
// 	cy->diameter = diam;
// 	cy->axis = v3d_norm(&vector);
// 	cy->height = height;
// 	cy->center = coo;
// 	new = (t_obj *) cy;
// 	new->type = OBJS;
// 	new->material = (t_rt_material){COLOR, {colors}};
// 	rt_backend_raytracer_cylinder(new);
// 	return (new);
// }
