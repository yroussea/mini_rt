/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cone_normal.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 03:00:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 00:59:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/option.h"
#include <ft/math.h>
#include <rt/render/backend/raytracer.h>

#if RT_RONDED_CONE_LINKED_SURFACE

t_vec3d	rt_backend_raytracer_colors_cone(
	const t_ray *ray,
	t_cone *cone
) {
	const t_vec3d	all_colors[2] = {cone->base.material.colors,
		cone->base.material.check_colors};
	t_vec3d			t;

	if (!(cone->base.material.type & CHECKERBOARD))
		return (*all_colors);
	rt_backend_raytracer_cone_twod_relative_point(&t, ray, cone);
	return (all_colors[rt_backend_raytracer_checkerboard(
				t.x - t.z, t.y)]);
}

t_vec3d	rt_backend_raytracer_cone_normal(
	t_ray *ray,
	t_cone *cone
) {
	const t_rt_material	mat = cone->base.material;
	double				m;
	t_vec3d				normal;
	t_vec3d				a;
	t_vec3d				v;

	if (cone->surface_type != RONDED)
		normal = v3d_mult(&cone->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cone->axis)));
	else
	{
		m = v3d_lensub(&ray->hit_point, &cone->center) / cone->cos;
		a = v3d_addmult(&cone->center, &cone->axis, m);
		v = v3d_normsub(&ray->hit_point, &a);
		normal = v3d_mult(&v, -ft_fsign(v3d_dot(&ray->direction, &v)));
	}
	if (mat.type & BUMP_MAP)
	{
		rt_backend_raytracer_cone_twod_relative_point(&a, ray, cone);
		normal = rt_backend_raytracer_bumpmap(&normal, mat.bump.map,
				rt_backend_raytracer_bumpmap_coo(a.x - a.z, a.y, mat.bump.size));
	}
	return (normal);
}

#else

t_vec3d	rt_backend_raytracer_colors_cone(
	const t_ray *ray,
	const t_cone *cone
) {
	const t_vec3d	all_colors[2] = {cone->base.material.colors,
		cone->base.material.check_colors};
	t_vec3d			t;

	if (!(cone->base.material.type & CHECKERBOARD))
		return (cone->base.material.colors);
	if (cone->surface_type != RONDED)
	{
		t = v3d_addmult(&cone->center, &cone->axis, cone->height);
		t = v3d_sub(&ray->hit_point, &t);
		return (rt_backend_raytracer_planar_color(
				t, m3d(cone->vec_udir, cone->vec_vdir, cone->axis),
				cone->base.material));
	}
	rt_backend_raytracer_cone_twod_relative_point(&t, ray, cone);
	return (all_colors[rt_backend_raytracer_checkerboard(
				t.x, t.y)]);
}

static void	rt_backend_raytracer_handle_bumpmap_normal(
	t_ray *ray,
	t_cone *cone,
	t_vec3d *normal
)
{
	t_vec3d				a;
	const t_rt_material	mat = cone->base.material;

	if (cone->surface_type != RONDED)
	{
		a = v3d_addmult(&cone->center, &cone->axis, cone->height);
		a = v3d_sub(&ray->hit_point, &a);
		a = m3d_solv(m3d(cone->vec_udir, cone->vec_vdir, cone->axis), a);
	}
	else
		rt_backend_raytracer_cone_twod_relative_point(&a, ray, cone);
	*normal = rt_backend_raytracer_bumpmap(normal, mat.bump.map, \
		rt_backend_raytracer_bumpmap_coo(a.x - a.z, a.y, mat.bump.size));
}

t_vec3d	rt_backend_raytracer_cone_normal(
	t_ray *ray,
	t_cone *cone
) {
	const t_rt_material	mat = cone->base.material;
	t_vec3d				normal;
	t_vec3d				a;

	if (cone->surface_type != RONDED)
		normal = v3d_mult(&cone->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cone->axis)));
	else
	{
		a = v3d_addmult(&cone->center, &cone->axis, \
				v3d_lensub(&ray->hit_point, &cone->center) / cone->cos);
		a = v3d_normsub(&ray->hit_point, &a);
		normal = v3d_mult(&a, -ft_fsign(v3d_dot(&ray->direction, &a)));
	}
	if (mat.type & BUMP_MAP)
		rt_backend_raytracer_handle_bumpmap_normal(ray, cone, &normal);
	return (normal);
}

#endif
