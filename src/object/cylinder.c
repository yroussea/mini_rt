/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/15 23:57:12 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include <object.h>
#include <maths.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

t_vec3d	get_cyl_normal(t_ray ray, void *obj);
float	cyl_inter(t_ray ray, void *obj);

t_objs	*cylinder(t_vec3d coo, t_vec3d vector, float height, float diam, t_vec3d colors)
{
	t_objs		*new;
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->diameter = diam;
	cy->axis = ft_vec3d_norm(vector);
	cy->sq_radius = powf(diam / 2, 2);
	cy->height = height;
	cy->center = coo;
	cy->top_center = ft_vec3d_add(coo, ft_vec3d_mult(vector, height));
	new = malloc(sizeof(t_objs));
	new->type = CYLINDER;
	new->obj = cy;
	new->colors = colors;
	new->get_normal = get_cyl_normal;
	new->intersection = cyl_inter;
	return (new);
}

static bool	quad(t_vec3d param, float *x1, float *x2)
{
	float	delta;

	delta = powf(param.y, 2) - 4 * param.x * param.z;
	if (delta < 0)
		return (0);
	delta = sqrtf(delta);
	*x1 = (-param.y + delta) / (2 * param.x);
	*x2 = (-param.y - delta) / (2 * param.x);
	return (1);
}

bool	infinite_cyl_inter(t_ray ray, t_cylinder *cy, float *t1, float *t2)
{
	t_vec3d		param;
	t_vec3d		x;
	float		var[5];

	x = ft_vec3d_sub(ray.point, cy->center);
	var[0] = ft_vec3d_dot(x, x);
	var[1] = ft_vec3d_dot(x, cy->axis);
	var[2] = ft_vec3d_dot(ray.direction, x);
	var[3] = ft_vec3d_dot(ray.direction, ray.direction);
	var[4] = ft_vec3d_dot(ray.direction, cy->axis);
	param.x = var[3] - powf(var[4], 2);
	param.y = 2 * (var[2] - var[4] * var[1]);
	param.z = var[0] - powf(var[1], 2) - cy->sq_radius;
	if (!quad(param, t1, t2))
		return (0);
	if (*t1 < EPSILON && *t2 < EPSILON)
		return (0);
	return (1);
}

bool	valid_cyl_inter(float t, t_ray ray, t_cylinder *cy, float *t_plane)
{
	float		m;
	t_vec3d		hit;

	hit = ft_vec3d_add(ray.point, ft_vec3d_mult(ray.direction, t));
	m = ft_vec3d_dot(ft_vec3d_sub(hit, cy->center), cy->axis);
	if (m < EPSILON)
	{
		*t_plane = plane_intersect(ray, cy->axis, cy->center);
		return (0);
	}
	if (m > cy->height - EPSILON)
	{
		*t_plane = plane_intersect(ray, cy->axis, cy->top_center);
		return (0);
	}
	return (1);
}

float	passing_through(t_ray ray, t_cylinder *cy)
{
	float		t_plane_bottom;
	t_vec3d		hit;

	t_plane_bottom = plane_intersect(ray, cy->axis, cy->center);
	if (t_plane_bottom < 0)
		return (-1);
	hit = ft_vec3d_add(ray.point, ft_vec3d_mult(ray.direction, t_plane_bottom));
	if (ft_vec3d_len(ft_vec3d_sub(hit, cy->center)) > cy->diameter / 2)
		return (-1);
	return (closer(t_plane_bottom, plane_intersect(ray, cy->axis, cy->top_center)));
}

float	cyl_inter(t_ray ray, void *obj)
{
	t_cylinder	*cy;
	float		t1;
	float		t2;
	float		t_plane;

	cy = obj;
	if (!infinite_cyl_inter(ray, obj, &t1, &t2))
		return (passing_through(ray, cy));
	if (!valid_cyl_inter(t1, ray, cy, &t_plane))
		t1 = -1;
	if (!valid_cyl_inter(t2, ray, cy, &t_plane))
		t2 = -1;
	if (t1 < 0 && t2 < 0)
		return (passing_through(ray, cy));
	if (t1 < 0)
		return (closer(t2, t_plane));
	if (t2 < 0)
		return (closer(t1, t_plane));
	return (closer(t1, t2));
}

t_vec3d	get_cyl_normal(t_ray ray, void *obj)
{
	t_cylinder	*cy;
	t_vec3d		a;
	float		m;

	cy = obj;
	m = ft_vec3d_dot(ft_vec3d_sub(ray.hit_point, cy->center), cy->axis);
	if (m >= cy->height - EPSILON)
		return (cy->axis);
	if (m <= EPSILON)
		return (ft_vec3d_sub((t_vec3d){0, 0, 0}, cy->axis));
	a = ft_vec3d_add(cy->center, ft_vec3d_mult(cy->axis, m));
	return (ft_vec3d_norm(ft_vec3d_sub(ray.hit_point, a)));
}
