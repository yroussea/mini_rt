/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 01:09:10 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/25 23:40:29 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/objs.h"
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static bool	infinite_cone_inter(t_ray ray, t_cone *cone, double *t1, double *t2)
{
	double			var[5];
	const double		sq_cos = powf(cone->cos, 2);
	const t_vec3d	x = v3d_sub(ray.point, cone->center);
	t_vec3d			param;

	var[0] = v3d_dot(ray.direction, cone->axis);
	var[1] = v3d_dot(x, cone->axis);
	var[2] = v3d_dot(ray.direction, v3d_mult(x, sq_cos));
	var[3] = v3d_dot(x, cone->axis);
	var[4] = v3d_dot(x, v3d_mult(x, sq_cos));
	param.x = powf(var[0], 2) - sq_cos;
	param.y = 2 * (var[0] * var[1] - var[2]);
	param.z = powf(var[3], 2) - var[4];
	if (!v3d_quadr(param, t1, t2))
		return (0);
	if (*t1 < 0 && *t2 < 0)
		return (0);
	return (1);
}

static bool	val_cone_inter(double t, t_ray ray, t_cone *cone)
{
	//marche que pour theta < 90°
	t_vec3d	hit;
	t_vec3d	x;
	double	dot;

	if (t < 0)
		return (0);
	hit = v3d_add(ray.point, v3d_mult(ray.direction, t));
	x = v3d_sub(hit, cone->center);
	dot = v3d_dot(v3d_norm(x), cone->axis);
	if (dot < 0)
		return (0);
	if (v3d_len(v3d_sub(hit, cone->center)) > cone->max_dist)
		return (0);
	return (1);
}

static double	plane_bottom_cone(t_ray ray, t_cone *cone)
{
	t_vec3d	hit;
	double	plane;
	t_vec3d	bottom;

	bottom = v3d_add(cone->center, v3d_mult(cone->axis, cone->height));
	plane = plane_intersect(ray, cone->axis, bottom);
	if (plane < 0)
		return (INFINITY);
	hit = v3d_add(ray.point, v3d_mult(ray.direction, plane));
	if (v3d_len(v3d_sub(bottom, hit)) > cone->height * tan(cone->theta))
		return (INFINITY);
	return (plane);
}

double	cone_inter(t_ray ray, void *obj)
{
	t_cone	*cone;
	double	t1;
	double	t2;

	cone = obj;
	if (!infinite_cone_inter(ray, cone, &t1, &t2))
		return (plane_bottom_cone(ray, cone));
	if (!val_cone_inter(t1, ray, cone))
		t1 = INFINITY;
	if (!val_cone_inter(t2, ray, cone))
		t2 = INFINITY;
	// return (ft_fmin(t1, ft_fmin(t2, INFINITY)));
	return (ft_fmin(t1, ft_fmin(t2, plane_bottom_cone(ray, cone))));
}


t_vec3d	get_cone_normal(t_ray ray, void *obj)
{
	//marche pas si plan
	t_cone		*cone;
	double		m;
	t_vec3d		a;
	t_vec3d		v;


	cone = obj;
	if (v3d_dot(v3d_norm(v3d_sub(ray.hit_point, cone->center)), cone->axis) < 0)
		return (v3d_mult(cone->axis, -ft_fsign(v3d_dot(ray.direction, cone->axis))));
	m = v3d_len(v3d_sub(ray.hit_point, cone->center)) / cone->cos;
	a = v3d_add(cone->center, v3d_mult(cone->axis, m));
	v = v3d_norm(v3d_sub(ray.hit_point, a));
	return (v3d_mult(v, -ft_fsign(v3d_dot(ray.direction, v))));
}

t_vec3d	get_colors_cone(t_ray ray, void *obj)
{
	const	t_objs	*cone = (t_objs *)obj;

	(void)ray;
	return (cone->material.colors);
}

t_objs	*cone(t_vec3d coo, t_vec3d vector, double height, double theta, t_vec3d colors)
{
	t_objs		*new;
	t_cone		*cone;

	cone = malloc(sizeof(t_cone));
	cone->axis = v3d_norm(vector);
	cone->height = height;
	cone->theta = theta / 180 * M_PI;
	cone->center = coo;
	cone->cos = cos(cone->theta);
	cone->max_dist = height / cone->cos;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = cone;
	new->material = (t_material){COLOR, colors};
	new->get_normal = get_cone_normal;
	new->get_colors = get_colors_cone;
	new->intersection = cone_inter;
	return (new);
}
