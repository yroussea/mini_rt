/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/06 21:52:08 by yroussea         ###   ########.fr       */
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
	delta = (b * b) - a * \
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
	const t_sphere	*s_sphere = (t_sphere *)sphere->obj;
	const t_vec3d	x = v3d_sub(ray.hit_point, s_sphere->center);
	const t_vec3d	all_colors[2] = {sphere->material.colors, (t_vec3d){0, 0, 0}};

	if (sphere->material.type == COLOR)
		return (*all_colors);
	const double phi = ft_fsign(x.z) * acos(x.x / sqrt(x.x * x.x + x.z * x.z));
	const double theta = acos(x.y / s_sphere->rayon);
	return (all_colors[rt_backend_raytracer_checkerboard(theta * 50, phi * 50)]);
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
