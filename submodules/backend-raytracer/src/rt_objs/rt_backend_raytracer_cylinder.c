/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/06 17:34:44 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/objs.h"
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray ray, void *obj)
{
	const t_cylinder	*cy = (t_cylinder *)obj;
	t_vec3d				a;
	double				m;

	if (cy->surface_type != RONDED)
		return (v3d_mult(cy->axis, -ft_fsign(v3d_dot(ray.direction, cy->axis))));
	m = v3d_dot(v3d_sub(ray.hit_point, cy->center), cy->axis);
	a = v3d_add(cy->center, v3d_mult(cy->axis, m));
	return (v3d_norm(v3d_sub(ray.hit_point, a)));
}

#define RT_RONDED_CYLINDER_LINK_CHECKERBOARD
#ifdef RT_RONDED_CYLINDER_LINK_CHECKERBOARD
t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		all_colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	double				u;
	t_vec3d				sol;

	if (cy->material.type == COLOR)
		return (*all_colors);
	u = v3d_dot(v3d_sub(ray.hit_point, c_cy->center), c_cy->axis);

	const t_vec3d	a = v3d_add(c_cy->center, v3d_mult(c_cy->axis, u));
	sol = m3d_solv(m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis), v3d_sub(ray.hit_point, a));
	const double	phy = ft_fsign(sol.y) * acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));

	const double	len_v = v3d_len(v3d_sub(a, ray.hit_point));

	return (all_colors[rt_backend_raytracer_checkerboard(u - len_v + c_cy->diameter / 2, phy / M_PI * 100)]);
}
#else
t_vec3d	rt_backend_raytracer_colors_cylinder(t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		all_colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d				hit;

	if (cy->material.type == COLOR)
		return (*all_colors);
	if (c_cy->surface_type != RONDED)
	{
		if (c_cy->surface_type == PLANE)
			hit = v3d_sub(ray.hit_point, c_cy->center);
		else
			hit = v3d_sub(ray.hit_point, c_cy->top_center);
		return (rt_backend_raytracer_planar_color(
			hit, m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis),
			cy->material.colors, cy->material.type
		));
	}

	const double u = v3d_dot(v3d_sub(ray.hit_point, c_cy->center), c_cy->axis);
	const t_vec3d a = v3d_add(c_cy->center, v3d_mult(c_cy->axis, u));

	const t_vec3d sol = m3d_solv(
		m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis), v3d_sub(ray.hit_point, a));
	const double phi = ft_fsign(sol.y) * acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));

	return (all_colors[rt_backend_raytracer_checkerboard(u, phi / M_PI * 100)]);
}
#endif


void	rt_backend_raytracer_cylinder(t_objs *obj)
{
	t_cylinder	*cy;

	cy = obj->obj;
	cy->vec_udir = v3d_norm(v3d(-cy->axis.y, cy->axis.x, 0));
	cy->vec_vdir = v3d_norm(v3d_cross(cy->axis, cy->vec_udir));
	cy->sq_radius = powf(cy->diameter / 2, 2);
	cy->top_center = v3d_add(cy->center, v3d_mult(cy->axis, cy->height));
	obj->get_normal = rt_backend_raytracer_cylinder_normal;
	obj->intersection = rt_backend_raytracer_cylinder_intersection;
	obj->get_colors = rt_backend_raytracer_colors_cylinder;
}

t_objs	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam, t_vec3d colors)
{
	t_objs		*new;
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->diameter = diam;
	cy->axis = v3d_norm(vector);
	cy->height = height;
	cy->center = coo;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = cy;
	new->material = (t_material){CHECKERBOARD, colors};
	rt_backend_raytracer_cylinder(new);
	return (new);
}
