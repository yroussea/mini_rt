/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/09 02:01:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <rt/render/backend/raytracer/objects.h>
#include <stdlib.h>
#include <math.h>

t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray *ray,
	t_cylinder *cy
) {
	t_vec3d				a;
	t_vec3d				new_point;
	double				m;

	if (cy->surface_type != RONDED)
		return (v3d_mult(&cy->axis,
				-ft_fsign(v3d_dot(&ray->direction, &cy->axis))));
	new_point = v3d_sub(&ray->hit_point, &cy->center);
	m = v3d_dot(&new_point, &cy->axis);
	a = v3d_addmult(&cy->center, &cy->axis, m);
	return (v3d_normsub(&ray->hit_point, &a));
}

static void	rt_backend_raytracer_cylinder_twod_relative_point(
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

#define RT_RONDED_CYLINDER_LINK_CHECKERBOARD 1
#if RT_RONDED_CYLINDER_LINK_CHECKERBOARD

t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray *ray,
	t_cylinder *cy
) {
	const t_vec3d		colors[2] = {cy->base.material.colors,
		(t_vec3d){0, 0, 0}};
	t_vec3d				tmp;

	if (cy->base.material.type == COLOR)
		return (*colors);
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x - tmp.z, tmp.y / M_PI * 100)]);
}

#else

t_vec3d	rt_backend_raytracer_colors_cylinder(
	t_ray *ray,
	t_cylinder *cy
) {
	const t_vec3d		colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d				tmp;

	if (cy->base.material.type == COLOR)
		return (*colors);
	if (cy->surface_type != RONDED)
	{
		if (cy->surface_type == PLANE)
			tmp = v3d_sub(&ray->hit_point, &cy->center);
		else
			tmp = v3d_sub(&ray->hit_point, &cy->top_center);
		return (rt_backend_raytracer_planar_color(
				tmp, m3d(cy->vec_udir, cy->vec_vdir, cy->axis),
				cy->base.material.colors, cy->base.material.type));
	}
	rt_backend_raytracer_cylinder_twod_relative_point(&tmp, ray, cy);
	return (colors[rt_backend_raytracer_checkerboard(
				tmp.x, tmp.y / M_PI * 100)]);
}

#endif

void	rt_backend_raytracer_cylinder(t_obj *obj)
{
	t_cylinder	*cy;
	t_vec3d		udir;
	t_vec3d		vdir;

	cy = (t_cylinder *)obj;
	udir = v3d(cy->axis.y + cy->axis.z, -cy->axis.x, -cy->axis.x);
	vdir = v3d_cross(&cy->axis, &udir);
	cy->vec_udir = v3d_norm(&udir);
	cy->vec_vdir = v3d_norm(&vdir);
	cy->sq_radius = cy->diameter * cy->diameter / 4;
	cy->top_center = v3d_addmult(&cy->center, &cy->axis, cy->height);
	obj->intersect = rt_backend_raytracer_cylinder_intersection;
	obj->calc_normal = rt_backend_raytracer_cylinder_normal;
	obj->calc_color = rt_backend_raytracer_colors_cylinder;
}

t_obj	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam, t_vec3d colors)
{
	t_obj		*new;
	t_cylinder	*cy;

	cy = rt_malloc_aligned(sizeof(t_cylinder), 32);
	cy->diameter = diam;
	cy->axis = v3d_norm(&vector);
	cy->height = height;
	cy->center = coo;
	new = (t_obj *) cy;
	new->type = OBJS;
	new->material = (t_rt_material){COLOR, {colors}};
	rt_backend_raytracer_cylinder(new);
	return (new);
}