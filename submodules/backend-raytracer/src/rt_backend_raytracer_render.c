/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_render.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:56:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/19 15:45:25 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/render/backend/raytracer/objs.h"
#include <rt/render/backend/raytracer.h>
#include <math.h>

t_color	rt_backend_raytracer_one_ray(t_ray ray, t_objs *all_objs)
{
	t_objs	*obj_hit;

	obj_hit = NULL;
	if (rt_backend_raytracer_find_obj_hit(&ray, all_objs, &obj_hit) != INFINITY)
		rt_backend_raytracer_get_shading(all_objs, obj_hit, &ray);
	return (ray.color);
}

//parsing
t_objs	*tmp(void)
{
	add_objects(plane((t_vec3d){0, 1, 0}, (t_vec3d){0, -50, 0}, (t_vec3d){0.2, 0.2, 0.2}));
	add_objects(sphere((t_vec3d){40, 0, 0}, 25, (t_vec3d){1, 0, 0}));
	add_objects(sphere((t_vec3d){-60, -20, 0}, 15, (t_vec3d){1, 1, 0}));
	add_objects(sphere((t_vec3d){0, -30, 0}, 5, (t_vec3d){0, 1, 0}));
	add_objects(cylinder((t_vec3d){0, 0, -20}, (t_vec3d){0, 1, 1}, 25, 25, (t_vec3d){0, 0, 1}));
	add_objects(light((t_vec3d){0}, 0.1, AMBIANCE_LIGHT,(t_vec3d){1, 1, 1}));
	add_objects(camera((t_vec3d){0, 0, -100}, (t_vec3d){0, 0, 1}, 179));
	add_objects(light((t_vec3d){10, 100, 0}, 1, POINT_LIGHT, (t_vec3d){1, 1, 1}));
	add_objects(light((t_vec3d){0, 100, 0}, 1, POINT_LIGHT, (t_vec3d){1, 1, 1}));
	add_objects(light((t_vec3d){-10, 100, 0}, 1, POINT_LIGHT, (t_vec3d){1, 1, 1}));
	return (add_objects(NULL));
}

#define FOV 90

//pixelisation!!
t_color	*rt_backend_raytracer_render(t_rt_backend *backend)
{
	const t_rt_backend_raytracer	*raytracer
		= (t_rt_backend_raytracer *)backend->data;
	size_t							y;
	size_t							x;
	t_ray							ray;
	static t_objs					*objs;

	y = 0;
	if (!objs)
		objs = tmp(); // a enlver :)
	// ray.center = first cam
	ray.center = (t_vec3d){0, 0, -100};
	while (y < backend->height)
	{
		x = 0;
		while (x < backend->width)
		{
			eye_rays(&ray, get_width(backend, x, FOV), get_height(backend, y));
			raytracer->buffer[y * backend->width + x] = \
				rt_backend_raytracer_one_ray(ray, objs);
			x++;
		}
		y++;
	}
	return (raytracer->buffer);
}
