/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/25 23:57:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

double	closer(double t1, double t2)
{
	if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
		return (t1);
	return (t2);
}

double	ray_sphere_intersect(t_ray ray, void *obj)
{
	t_vec3d	v;
	double	b;
	double	a;
	double	delta;

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
t_vec3d	get_colors_sphere(t_ray ray, void *obj)
{
	const t_objs	*sphere = (t_objs *)obj;
	const t_vec3d	x = ray.hit_point;

	if (sphere->material.type == COLOR)
		return (sphere->material.colors);
	double a = fabs(floor(x.x)) + fabs(floor(x.y)) + fabs(floor(x.z));
	if ((int)a % 2)
		return ((t_vec3d){0, 0, 0});
	return (sphere->material.colors);
}
t_objs	*sphere(t_vec3d center, double diameter, t_material material)
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
	new->material = material;
	new->get_colors = get_colors_sphere;
	new->get_normal = get_sphere_normal;
	new->intersection = ray_sphere_intersect;
	return (new);
}
