/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cylinder_intersection.c       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:47:27 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 12:58:40 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/objs.h"
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <math.h>

static bool	rt_be_rt_inf_cyl_inter(
	const t_ray *ray, const t_cylinder *cy, double *x1, double *x2)
{
	t_vec3d		param;
	t_vec3d		x;
	double		var[5];

	x = v3d_sub(&ray->point, &cy->center);
	var[0] = v3d_dot(&x, &x);
	var[1] = v3d_dot(&x, &cy->axis);
	var[2] = v3d_dot(&ray->direction, &x);
	var[3] = v3d_dot(&ray->direction, &ray->direction);
	var[4] = v3d_dot(&ray->direction, &cy->axis);
	param.x = var[3] - var[4] * var[4];
	param.y = 2 * (var[2] - var[4] * var[1]);
	param.z = var[0] - var[1] * var[1] - cy->sq_radius;
	if (!v3d_quadr(&param, x1, x2))
		return (0);
	if (*x1 < EPSILON && *x2 < EPSILON)
		return (0);
	return (1);
}

static bool	rt_be_rt_limit_cyl_inter(
	const double t, const t_ray *ray, const t_cylinder *cy)
{
	const t_vec3d	hit = v3d_addmult(&ray->point, &ray->direction, t);
	const t_vec3d	new_point = v3d_sub(&hit, &cy->center);
	const double	m = v3d_dot(&new_point, &cy->axis);

	if (m < 0)
		return (0);
	if (m > cy->height - 0)
		return (0);
	return (1);
}

static bool	rt_be_rt_limite_plane_inter(
	const t_ray *ray, const t_cylinder *cy,
	const double t, const t_vec3d center)
{
	t_vec3d		hit;

	if (t < 0 || t == INFINITY)
		return (0);
	hit = v3d_addmult(&ray->point, &ray->direction, t);
	if (v3d_lensub(&hit, &center) > cy->diameter / 2)
		return (0);
	return (1);
}

static double	rt_be_rt_open_cyl_inter(
	const t_cylinder *cy, const t_ray *ray)
{
	double	tmp;
	double	closer;

	if (rt_be_rt_inf_cyl_inter(ray, cy, &tmp, &closer))
	{
		if (!rt_be_rt_limit_cyl_inter(tmp, ray, cy))
			tmp = INFINITY;
		if (!rt_be_rt_limit_cyl_inter(closer, ray, cy))
			return (tmp);
		return (ft_fmin(closer, tmp));
	}
	return (INFINITY);
}

double	rt_backend_raytracer_cylinder_intersection(
	t_ray *ray, void *obj)
{
	static double	tmp = INFINITY;
	double			closer;
	t_cylinder		*cy;

	cy = obj;
	cy->surface_type = RONDED;
	closer = rt_be_rt_open_cyl_inter(cy, ray);
	tmp = rt_backend_raytracer_planar_intersect(ray, cy->axis, cy->center);
	if (rt_be_rt_limite_plane_inter(ray, cy, tmp, cy->center))
	{
		if (tmp < closer)
			cy->surface_type = PLANE;
		if (tmp < closer)
			closer = tmp;
	}
	tmp = rt_backend_raytracer_planar_intersect(ray, cy->axis, cy->top_center);
	if (rt_be_rt_limite_plane_inter(ray, cy, tmp, cy->top_center))
	{
		if (tmp < closer)
			cy->surface_type = SECOND_PLANE;
		if (tmp < closer)
			closer = tmp;
	}
	return (closer);
}
