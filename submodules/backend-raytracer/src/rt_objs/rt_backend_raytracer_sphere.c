/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_sphere.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 14:18:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

double	rt_backend_raytracer_sphere_intersection(
	const t_ray *ray, void *obj)
{
	const t_vec3d	v = v3d_sub(&ray->point, &(((t_sphere *)obj)->center));
	t_vec3d			param;
	double			delta;
	double			t1;
	double			t2;

	param.x = v3d_dot(&ray->direction, &ray->direction);
	param.y = v3d_dot(&v, &ray->direction);
	param.z = ((v3d_len(&v) - (*(t_sphere *)obj).dot_production_rayon));
	delta = (param.y * param.y) - parma.x * param.z;
	if (delta >= 0)
	{
		t1 = (-b + sqrtf(delta)) / a;
		t2 = (-b - sqrtf(delta)) / a);
		if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
			return (t1);
		return (t2);
	}
	return (-1);
}

t_vec3d	rt_backend_raytracer_sphere_normal(
	const t_ray ray, void *obj)
{
	return (v3d_normsub(&ray.hit_point, &(((t_sphere *)obj)->center)));
}

static void	rt_backend_raytracer_sphere_twod_relative_point(
	t_vec3d *relativ_coo, const t_ray *ray, const t_sphere *sph)
{
	const t_vec3d	x = v3d_sub(&ray.hit_point, &(sph->center));

	relative_coo->x = ft_fsign(x.z) * acos(x.x / sqrt(x.x * x.x + x.z * x.z));
	relative_coo->y = acos(x.y / sph->rayon);
}

t_vec3d	rt_backend_raytracer_colors_sphere(t_ray ray, void *obj)
{
	const t_objs	*sphere = (t_objs *)obj;
	const t_sphere	*s_sphere = (t_sphere *)sphere->obj;
	const t_vec3d	colors[2] = {sphere->material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d			tmp;

	if (sphere->material.type == COLOR)
		return (*colors);
	rt_backend_raytracer_sphere_twod_relative_point(&tmp, ray, s_sphere);
	return (colors[rt_backend_raytracer_checkerboard(tmp.x * 50, tmp.y * 50)]);
}

void	rt_backend_raytracer_sphere(t_objs *obj)
{
	t_sphere	*sph;

	sph = obj;
	sph->dot_production_rayon = sph->rayon * sph->rayon;
	obj->get_colors = rt_backend_raytracer_colors_sphere;
	obj->get_normal = rt_backend_raytracer_sphere_normal;
	obj->intersection = rt_backend_raytracer_sphere_intersection;
}

t_objs	*sphere(t_vec3d center, double diameter, t_material material)
{
	t_objs		*new;
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	sph->rayon = diameter / 2;
	sph->center = center;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = sph;
	new->material = material;
	rt_backend_raytracer_sphere(new);
	return (new);
}
