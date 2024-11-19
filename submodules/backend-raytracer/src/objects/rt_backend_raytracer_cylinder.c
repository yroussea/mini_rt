/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 16:50:53 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/objects.h"
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

static void	rt_backend_raytracer_calc_aabbx_cylinder(t_cylinder *cy)
{
	t_vec3d		tmp;
	t_vec3d		tmp2;
	t_vec3d		high;

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
}

void	rt_backend_raytracer_cylinder(t_obj *obj)
{
	t_cylinder	*cy;
	t_vec3d		tmp;

	cy = (t_cylinder *)obj;
	cy->axis = v3d_norm(&cy->axis);
	tmp = v3d(cy->axis.y + cy->axis.z, -cy->axis.x, -cy->axis.x);
	cy->vec_udir = v3d_norm(&tmp);
	tmp = v3d_cross(&cy->axis, &cy->vec_udir);
	cy->vec_vdir = v3d_norm(&tmp);
	cy->sq_radius = cy->diameter * cy->diameter / 4;
	cy->top_center = v3d_addmult(&cy->center, &cy->axis, cy->height);
	rt_backend_raytracer_calc_aabbx_cylinder(cy);
	obj->intersect = rt_backend_raytracer_cylinder_intersection;
	obj->calc_normal = rt_backend_raytracer_cylinder_normal;
	obj->calc_color = rt_backend_raytracer_colors_cylinder;
}
