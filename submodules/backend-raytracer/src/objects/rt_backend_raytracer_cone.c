/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cone.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:09:10 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/14 21:57:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <math.h>
#include <stdlib.h>

t_vec3d	rt_backend_raytracer_cone_normal(
	t_ray *ray,
	t_cone *cone
) {
	double				m;
	t_vec3d				a;
	t_vec3d				v;

	if (cone->surface_type != RONDED)
		return (v3d_mult(&cone->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cone->axis))));
	m = v3d_lensub(&ray->hit_point, &cone->center) / cone->cos;
	a = v3d_addmult(&cone->center, &cone->axis, m);
	v = v3d_normsub(&ray->hit_point, &a);
	return (v3d_mult(&v, -ft_fsign(v3d_dot(&ray->direction, &v))));
}

static void	rt_backend_raytracer_cone_twod_relative_point(
	t_vec3d *relative_coo,
	const t_ray *ray,
	const t_cone *cone
) {
	const double	u = v3d_lensub(&ray->hit_point, &cone->center) / cone->cos;
	const t_vec3d	a = v3d_addmult(&cone->center, &cone->axis, u);
	const t_vec3d	sol = m3d_solv(m3d(cone->vec_udir, cone->vec_vdir,
				cone->axis), v3d_sub(&ray->hit_point, &a));

	relative_coo->x = u;
	relative_coo->y = ft_fsign(sol.y) * \
		acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));
	relative_coo->z = v3d_lensub(&a, &ray->hit_point) - cone->theta * u;
}

#define RT_RONDED_CONE_LINK_CHECKERBOARD 1 
#if RT_RONDED_CONE_LINK_CHECKERBOARD

t_vec3d	rt_backend_raytracer_colors_cone(
	const t_ray *ray,
	t_cone *cone
) {
	const t_vec3d	all_colors[2] = {cone->base.material.colors,
		cone->base.material.check_colors};
	t_vec3d			t;

	if (cone->base.material.type == COLOR)
		return (*all_colors);
	rt_backend_raytracer_cone_twod_relative_point(&t, ray, cone);
	return (all_colors[rt_backend_raytracer_checkerboard(
				t.x - t.z, t.y / M_PI * 100)]);
}

#else

t_vec3d	rt_backend_raytracer_colors_cone(
	const t_ray *ray,
	const t_cone *cone
) {
	const t_vec3d	all_colors[2] = {cone->base.material.colors,
		cone->base.material.check_colors};
	t_vec3d			t;

	if (cone->base.material.type == COLOR)
		return (cone->base.material.colors);
	if (cone->surface_type != RONDED)
	{
		t = v3d_addmult(&c_cone->center, c_cone->axis, c_cone->height);
		t = v3d_sub(&ray.hit_point, &t);
		return (rt_backend_raytracer_planar_color(
				t, m3d(c_cone->vec_udir, c_cone->vec_vdir, c_cone->axis),
				cone->material.colors, cone->material.type));
	}
	rt_backend_raytracer_cone_twod_relative_point(&t, ray, c_cone);
	return (all_colors[rt_backend_raytracer_checkerboard(
				t.x, t.y / M_PI * 100)]);
}

#endif

void	rt_backend_raytracer_cone(t_obj *obj)
{
	t_cone		*cone;
	t_vec3d		t;
	t_vec3d		top;
	t_vec3d		high;

	cone = (t_cone *)obj;
	t = v3d(cone->axis.y + cone->axis.z, -cone->axis.x, -cone->axis.x);
	cone->vec_udir = v3d_norm(&t);
	t = v3d_cross(&cone->axis, &cone->vec_udir);
	cone->vec_vdir = v3d_norm(&t);
	cone->cos = cos(cone->theta);
	cone->tan = tan(cone->theta);
	cone->max_dist = cone->height / cone->cos;
	top = v3d_addmult(&cone->center, &cone->axis, cone->height);
	t = rt_backend_raytracer_highest_point_circle(cone->vec_udir,
			cone->vec_vdir, top, cone->height * cone->tan);
	high = v3d_max(&t, &top);
	t = rt_backend_raytracer_lowest_point_circle(cone->vec_udir,
			cone->vec_vdir, top, cone->height * cone->tan);
	rt_backend_raytracer_creating_aabbx(&cone->aabbx, high, v3d_min(&t, &top));
	obj->intersect = rt_backend_raytracer_cone_intersection;
	obj->calc_normal = rt_backend_raytracer_cone_normal;
	obj->calc_color = rt_backend_raytracer_colors_cone;
}

// t_obj	*cone(t_vec3d coo, t_vec3d vector, double height, double theta, t_vec3d colors)
// {
// 	t_obj			*new;
// 	t_cone			*cone;
//
// 	cone = rt_malloc_aligned(sizeof(t_cone), 32);
// 	if (!cone)
// 		return (NULL);
// 	cone->axis = v3d_norm(&vector);
// 	cone->height = height;
// 	//limiter theta a 90degree
// 	cone->theta = theta / 180 * M_PI;
// 	cone->center = coo;
// 	new = (t_obj *) cone;
// 	new->type = OBJS;
// 	new->material = (t_rt_material){CHECKERBOARD, colors, };
// 	rt_backend_raytracer_cone(new);
// 	return (new);
// }
