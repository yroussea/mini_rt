/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:15:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 17:54:10 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

static bool	infinite_cyl_inter(t_ray ray, t_cylinder *cy, double *t1, double *t2)
{
	t_vec3d		param;
	t_vec3d		x;
	float		var[5];

	x = v3d_sub(ray.point, cy->center);
	var[0] = v3d_dot(x, x);
	var[1] = v3d_dot(x, cy->axis);
	var[2] = v3d_dot(ray.direction, x);
	var[3] = v3d_dot(ray.direction, ray.direction);
	var[4] = v3d_dot(ray.direction, cy->axis);
	param.x = var[3] - powf(var[4], 2);
	param.y = 2 * (var[2] - var[4] * var[1]);
	param.z = var[0] - powf(var[1], 2) - cy->sq_radius;
	if (!v3d_quadr(param, t1, t2))
		return (0);
	if (*t1 < EPSILON && *t2 < EPSILON)
		return (0);
	return (1);
}

static bool	valid_cyl_inter(float t, t_ray ray, t_cylinder *cy, float *t_plane)
{
	float		m;
	t_vec3d		hit;

	hit = v3d_add(ray.point, v3d_mult(ray.direction, t));
	m = v3d_dot(v3d_sub(hit, cy->center), cy->axis);
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

static float	passing_through(t_ray ray, t_cylinder *cy)
{
	float		t_plane_bottom;
	t_vec3d		hit;

	t_plane_bottom = plane_intersect(ray, cy->axis, cy->center);
	if (t_plane_bottom < 0)
		return (-1);
	hit = v3d_add(ray.point, v3d_mult(ray.direction, t_plane_bottom));
	if (v3d_len(v3d_sub(hit, cy->center)) > cy->diameter / 2)
		return (-1);
	return (closer(t_plane_bottom, plane_intersect(ray, cy->axis, cy->top_center)));
}

float	cyl_inter(t_ray ray, void *obj)
{
	t_cylinder	*cy;
	double		t1;
	double		t2;
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
		t1 = t_plane;
	if (t2 < 0)
		t2 = t_plane;
	if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
		return (t1);
	return (t2);
}

t_vec3d	get_cyl_normal(t_ray ray, void *obj)
{
	t_cylinder	*cy;
	t_vec3d		a;
	float		m;

	cy = obj;
	m = v3d_dot(v3d_sub(ray.hit_point, cy->center), cy->axis);
	if (m >= cy->height - EPSILON)
		return (cy->axis);
	if (m <= EPSILON)
		return (v3d_sub((t_vec3d){0, 0, 0}, cy->axis));
	a = v3d_add(cy->center, v3d_mult(cy->axis, m));
	return (v3d_norm(v3d_sub(ray.hit_point, a)));
}

t_objs	*cylinder(t_vec3d coo, t_vec3d vector, float height, float diam, t_vec3d colors)
{
	t_objs		*new;
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->diameter = diam;
	cy->axis = v3d_norm(vector);
	cy->sq_radius = powf(diam / 2, 2);
	cy->height = height;
	cy->center = coo;
	cy->top_center = v3d_add(coo, v3d_mult(vector, height));
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = cy;
	new->colors = colors;
	new->get_normal = get_cyl_normal;
	new->intersection = cyl_inter;
	return (new);
}
