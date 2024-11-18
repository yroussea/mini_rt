/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_cone_intersection.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:25:22 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:36:07 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <rt/render/backend/raytracer.h>

static bool	rt_be_rt_inf_cone_inter(
	const t_ray *ray,
	const t_cone *cone,
	double *t1,
	double *t2
) {
	double			var[5];
	const double	sq_cos = cone->cos * cone->cos;
	const t_vec3d	x = v3d_sub(&ray->point, &cone->center);
	t_vec3d			param;

	var[0] = v3d_dot(&ray->direction, &cone->axis);
	var[1] = v3d_dot(&x, &cone->axis);
	param = v3d_mult(&x, sq_cos);
	var[2] = v3d_dot(&ray->direction, &param);
	var[3] = v3d_dot(&x, &cone->axis);
	var[4] = v3d_dot(&x, &param);
	param.x = var[0] * var[0] - sq_cos;
	param.y = 2 * (var[0] * var[1] - var[2]);
	param.z = var[3] * var[3] - var[4];
	if (!v3d_quadr(&param, t1, t2))
		return (0);
	if (*t1 < 0 && *t2 < 0)
		return (0);
	return (1);
}

static bool	rt_be_rt_limite_cone_inter(
	const double t,
	const t_ray *ray,
	const t_cone *cone
) {
	const t_vec3d	hit = v3d_addmult(&ray->point, &ray->direction, t);
	const t_vec3d	x = v3d_normsub(&hit, &cone->center);
	const double	dot = v3d_dot(&x, &cone->axis);

	if (dot < 0)
		return (0);
	if (v3d_lensub(&hit, &cone->center) > cone->max_dist)
		return (0);
	return (1);
}

static double	rt_be_rt_limite_plan_inter(
	const t_ray *ray,
	const t_cone *cone
) {
	t_vec3d			hit;
	const t_vec3d	bottom = v3d_addmult(
			&cone->center, &cone->axis, cone->height);
	const double	plane = rt_backend_raytracer_planar_intersect(
			ray, cone->axis, bottom);

	if (plane < 0)
		return (INFINITY);
	hit = v3d_addmult(&ray->point, &ray->direction, plane);
	if (v3d_lensub(&bottom, &hit) > cone->height * cone->tan)
		return (INFINITY);
	return (plane);
}

double	rt_backend_raytracer_cone_intersection(
	t_ray *ray, t_cone *cone)
{
	double	t1;
	double	t2;
	double	closer;

	if (!rt_backend_raytracer_aabbx_inter(ray, cone->aabbx))
		return (-1);
	closer = INFINITY;
	cone->surface_type = RONDED;
	if (rt_be_rt_inf_cone_inter(ray, cone, &t1, &t2))
	{
		if (t1 < 0 || !rt_be_rt_limite_cone_inter(t1, ray, cone))
			t1 = INFINITY;
		if (t2 < 0 || !rt_be_rt_limite_cone_inter(t2, ray, cone))
			t2 = INFINITY;
		closer = ft_fmin(t2, t1);
	}
	t1 = rt_be_rt_limite_plan_inter(ray, cone);
	if (t1 < closer)
	{
		closer = t1;
		cone->surface_type = PLANE;
	}
	return (closer);
}
