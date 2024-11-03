/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/03 19:19:31 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

static bool	infinite_cyl_inter(t_ray ray, t_cylinder *cy, double *tmp, double *closer)
{
	t_vec3d		param;
	t_vec3d		x;
	double		var[5];

	x = v3d_sub(ray.point, cy->center);
	var[0] = v3d_dot(x, x);
	var[1] = v3d_dot(x, cy->axis);
	var[2] = v3d_dot(ray.direction, x);
	var[3] = v3d_dot(ray.direction, ray.direction);
	var[4] = v3d_dot(ray.direction, cy->axis);
	param.x = var[3] - powf(var[4], 2);
	param.y = 2 * (var[2] - var[4] * var[1]);
	param.z = var[0] - powf(var[1], 2) - cy->sq_radius;
	if (!v3d_quadr(param, tmp, closer))
		return (0);
	if (*tmp < EPSILON && *closer < EPSILON)
		return (0);
	return (1);
}

static bool	valid_cyl_inter(double t, t_ray ray, t_cylinder *cy)
{
	double		m;
	t_vec3d		hit;

	hit = v3d_add(ray.point, v3d_mult(ray.direction, t));
	m = v3d_dot(v3d_sub(hit, cy->center), cy->axis);
	if (m < 0)
		return (0);
	if (m > cy->height - 0)
		return (0);
	return (1);
}

static bool	valid_plane_inter(t_ray ray, t_cylinder *cy, double t, t_vec3d center)
{
	t_vec3d		hit;

	if (t < 0 || t == INFINITY)
		return (0);
	hit = v3d_add(ray.point, v3d_mult(ray.direction, t));
	if (v3d_len(v3d_sub(hit, center)) > cy->diameter / 2)
		return (0);
	return (1);
}

bool	set_at_min(double a, double b, double *res)
{
	if (a < b)
	{
		*res = a;
		return (0);
	}
	*res = b;
	return (1);
}

double	cylinder_inter(t_ray ray, void *obj)
{
	t_cylinder	*cy = (t_cylinder *)obj;
	double				tmp = INFINITY;
	double				closer = INFINITY;

	cy->surface_type = RONDED;
	if (infinite_cyl_inter(ray, cy, &tmp, &closer))
	{
		if (!valid_cyl_inter(tmp, ray, cy))
			tmp = INFINITY;
		if (!valid_cyl_inter(closer, ray, cy))
			closer = INFINITY;
		closer = ft_fmin(closer, tmp);
	}
	tmp = rt_backend_raytracer_planar_intersect(ray, cy->axis, cy->center);
	if (valid_plane_inter(ray, cy, tmp, cy->center))
	{
		if (set_at_min(closer, tmp, &closer))
			cy->surface_type = PLANE;
	}
	tmp = rt_backend_raytracer_planar_intersect(ray, cy->axis, cy->top_center);
	if (valid_plane_inter(ray, cy, tmp, cy->top_center))
	{
		if (set_at_min(closer, tmp, &closer))
			cy->surface_type = SECOND_PLANE;
	}
	return (closer);
}

t_vec3d	get_cyl_normal(t_ray ray, void *obj)
{
	t_cylinder	*cy;
	t_vec3d		a;
	double		m;

	cy = obj;
	if (cy->surface_type != RONDED)
		return (v3d_mult(cy->axis, -ft_fsign(v3d_dot(ray.direction, cy->axis))));
	m = v3d_dot(v3d_sub(ray.hit_point, cy->center), cy->axis);
	a = v3d_add(cy->center, v3d_mult(cy->axis, m));
	return (v3d_norm(v3d_sub(ray.hit_point, a)));
}

// #define RT_RONDED_CYLINDER_LINK_CHECKERBOARD
#ifdef RT_RONDED_CYLINDER_LINK_CHECKERBOARD
t_vec3d	get_colors_cyl(t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		all_colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};

	if (cy->material.type == COLOR)
		return (*all_colors);

	const double u = v3d_dot(v3d_sub(ray.hit_point, c_cy->center), c_cy->axis);
	const t_vec3d a = v3d_add(c_cy->center, v3d_mult(c_cy->axis, u));

	const t_vec3d sol = m3d_solv(
		m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis), v3d_sub(ray.hit_point, a));
	const double phi = ft_fsign(sol.y) * acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));

	return (all_colors[rt_backend_raytracer_checkerboard(u, phi / M_PI * 100)]);
}
#else
t_vec3d	get_colors_cyl(t_ray ray, void *obj)
{
	const t_objs		*cy = (t_objs *)obj;
	const t_cylinder	*c_cy = (t_cylinder *)cy->obj;
	const t_vec3d		all_colors[2] = {cy->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d				hit;

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
	if (cy->material.type == COLOR)
		return (*all_colors);

	const double u = v3d_dot(v3d_sub(ray.hit_point, c_cy->center), c_cy->axis);
	const t_vec3d a = v3d_add(c_cy->center, v3d_mult(c_cy->axis, u));

	const t_vec3d sol = m3d_solv(
		m3d(c_cy->vec_udir, c_cy->vec_vdir, c_cy->axis), v3d_sub(ray.hit_point, a));
	const double phi = ft_fsign(sol.y) * acos(sol.x / sqrt(sol.x * sol.x + sol.y * sol.y));

	return (all_colors[rt_backend_raytracer_checkerboard(u, phi / M_PI * 100)]);
}
#endif



t_objs	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam, t_vec3d colors)
{
	t_objs		*new;
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->diameter = diam;
	cy->axis = v3d_norm(vector);
	cy->vec_udir = v3d_norm(v3d(-cy->axis.y, cy->axis.x, 0));
	cy->vec_vdir = v3d_norm(v3d_cross(cy->axis, cy->vec_udir));

	cy->sq_radius = powf(diam / 2, 2);
	cy->height = height;
	cy->center = coo;
	cy->top_center = v3d_add(coo, v3d_mult(cy->axis, height));
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = cy;
	new->material = (t_material){CHECKERBOARD, colors};
	new->get_normal = get_cyl_normal;
	new->intersection = cylinder_inter;
	new->get_colors = get_colors_cyl;
	return (new);
}
