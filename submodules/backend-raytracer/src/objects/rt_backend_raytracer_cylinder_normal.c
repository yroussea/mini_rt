/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder_normal.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:37:56 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 00:58:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/option.h"
#include <ft/math.h>
#include <rt/render/backend/raytracer.h>

#if RT_RONDED_CYLINDER_LINK_CHECKERBOARD

t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray *ray,
	t_cylinder *cy
) {
	const t_vec3d		colors[2] = {cy->base.material.colors,
		cy->base.material.check_colors};
	t_vec3d				tmp;

	if (!(cy->base.material.type & CHECKERBOARD))
		return (*colors);
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x - tmp.z, tmp.y)]);
}

t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray *ray,
	t_cylinder *cy
) {
	const t_rt_material	mat = cy->base.material;
	double				m;
	t_vec3d				a;
	t_vec3d				normal;
	t_vec3d				new_point;

	if (cy->surface_type != RONDED)
		normal = v3d_mult(&cy->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cy->axis)));
	else
	{
		new_point = v3d_sub(&ray->hit_point, &cy->center);
		m = v3d_dot(&new_point, &cy->axis);
		a = v3d_addmult(&cy->center, &cy->axis, m);
		normal = v3d_normsub(&ray->hit_point, &a);
	}
	if (mat.type & BUMP_MAP)
	{
		rt_backend_raytracer_cylinder_twod_relative_point(&a, ray, cy);
		normal = rt_backend_raytracer_bumpmap(&normal, mat.bump.map,
				rt_backend_raytracer_bumpmap_coo(a.x - a.z, a.y, mat.bump.size));
	}
	return (normal);
}

#else

t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray *ray,
	t_cylinder *cy
) {
	const t_vec3d		colors[2] = {cy->base.material.colors,
		cy->base.material.check_colors};
	t_vec3d				tmp;

	if (!(cy->base.material.type & CHECKERBOARD))
		return (*colors);
	if (cy->surface_type != RONDED)
	{
		if (cy->surface_type == PLANE)
			tmp = v3d_sub(&ray->hit_point, &cy->center);
		else
			tmp = v3d_sub(&ray->hit_point, &cy->top_center);
		return (rt_backend_raytracer_planar_color(
				tmp, m3d(cy->vec_udir, cy->vec_vdir, cy->axis),
				cy->base.material));
	}
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x, tmp.y)]);
}

static void	rt_backend_raytracer_handle_bumpmap_normal(
	const t_ray *ray,
	const t_cylinder *cy,
	t_vec3d *normal
)
{
	t_vec3d				a;
	const t_rt_material	mat = cy->base.material;

	if (cy->surface_type != RONDED)
	{
		if (cy->surface_type == PLANE)
			a = v3d_sub(&ray->hit_point, &cy->center);
		else
			a = v3d_sub(&ray->hit_point, &cy->top_center);
		a = m3d_solv(m3d(cy->vec_udir, cy->vec_vdir, cy->axis), a);
	}
	else
		rt_backend_raytracer_cylinder_twod_relative_point(&a, ray, cy);
	*normal = rt_backend_raytracer_bumpmap(normal, mat.bump.map, \
		rt_backend_raytracer_bumpmap_coo(a.x - a.z, a.y, mat.bump.size));
}

t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray *ray,
	t_cylinder *cy
) {
	const t_rt_material	mat = cy->base.material;
	double				m;
	t_vec3d				a;
	t_vec3d				normal;
	t_vec3d				new_point;

	if (cy->surface_type != RONDED)
		normal = v3d_mult(&cy->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cy->axis)));
	else
	{
		new_point = v3d_sub(&ray->hit_point, &cy->center);
		m = v3d_dot(&new_point, &cy->axis);
		a = v3d_addmult(&cy->center, &cy->axis, m);
		normal = v3d_normsub(&ray->hit_point, &a);
	}
	if (mat.type & BUMP_MAP)
		rt_backend_raytracer_handle_bumpmap_normal(ray, cy, &normal);
	return (normal);
}

#endif
