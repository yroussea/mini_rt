/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/20 00:03:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

float	closer(float t1, float t2)
{
	if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
		return (t1);
	return (t2);
}

float	ray_sphere_intersect(t_ray ray, void *obj)
{
	t_vec3d	v;
	float	b;
	float	a;
	float	delta;

	v = v3d_sub(ray.point, (*(t_sphere *)obj).center);
	b = v3d_dot(v, ray.direction);
	a = v3d_dot(ray.direction, ray.direction);
	delta = pow(b, 2) - a * \
		((v3d_dot(v, v) - (*(t_sphere *)obj).dot_production_rayon));
	if (delta >= 0)
		return (closer((-b + sqrtf(delta)) / a, (-b - sqrtf(delta)) / a));
	return (-1);
}

t_vec3d	get_sphere_normal(t_ray ray, void *obj)
{
	return (v3d_norm(v3d_sub(ray.hit_point, (*(t_sphere *)obj).center)));
}

t_objs	*sphere(t_vec3d center, float diameter, t_vec3d colors)
{
	t_objs		*new;
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	sph->rayon = diameter / 2;
	sph->dot_production_rayon = sph->rayon * sph->rayon;
	sph->center = center;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = sph;
	new->colors = colors;
	new->get_normal = get_sphere_normal;
	new->intersection = ray_sphere_intersect;
	return (new);
}
