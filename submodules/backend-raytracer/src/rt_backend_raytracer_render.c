/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_render.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:56:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/07 00:30:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <math.h>
#include <rt/log.h>
#include "rt/render/backend/raytracer/objs.h"
#include "rt/render/backend/raytracer/ray.h"
#include <rt/render/backend/raytracer.h>

t_color	rt_backend_raytracer_one_ray(t_ray *ray, t_objs *all_objs)
{
	t_objs	*obj_hit;

	obj_hit = NULL;
	if (rt_backend_raytracer_find_obj_hit(ray, all_objs, &obj_hit) != INFINITY)
		rt_backend_raytracer_get_shading(all_objs, obj_hit, ray);
	return (ray->color);
}

//parsing
t_objs	*tmp(void)
{
	// add_objects(plane((t_vec3d){1, 0, 1}, (t_vec3d){-20, 0, 500}, (t_material){COLOR,(t_vec3d){1,1,1}}));
	add_objects(sphere((t_vec3d){70*2, 20, 0}, 30, (t_material){COLOR,(t_vec3d){1,1,0}}));
	add_objects(sphere((t_vec3d){60*2, -20, 0}, 30, (t_material){COLOR,(t_vec3d){1,1,0}}));
	add_objects(camera((t_vec3d){0, 0, -100}, (t_vec3d){0, 0, 1}, 179));
	add_objects(light((t_vec3d){0}, .1, AMBIANCE_LIGHT,(t_vec3d){1, 1, 1}));
	add_objects(light((t_vec3d){0, 0, -100}, 1, POINT_LIGHT, (t_vec3d){1, 1, 1}));

	// add_objects(cylinder(
	// 	(t_vec3d){0, 0, 0},
	// 	(t_vec3d){1, 1, -2},
	// 	50,
	// 	30,
	// 	(t_vec3d){1,0,1}
	// ));
	add_objects(cone(
		(t_vec3d){-60, 1, 0},
		(t_vec3d){1, 1, -.7},
		50,
		30,
		(t_vec3d){1,0,1}
	));
	//
	return (add_objects(NULL));
}

#define FOV M_PI / 2

static t_ray	*rt_backend_raytracer_rays(t_rt_backend *backend,
					t_vec3d center, bool invalidate)
{
	static t_ray	*array = 0;
	size_t			i;

	if (invalidate)
	{
		free(array);
		array = NULL;
	}
	if (array)
		return (array);
	array = ft_calloc(backend->width * backend->height, sizeof(t_ray));
	if (array)
	{
		i = 0;
		while (i < backend->width * backend->height)
		{
			array[i].center = center;
			eye_rays(&array[i], get_width(backend, i % backend->width),
				get_height(backend, i / backend->width), FOV);
			i++;
		}
	}
	return (array);
}

t_color	*rt_backend_raytracer_render(t_rt_backend *backend)
{
	t_rt_backend_raytracer	*raytracer;
	size_t					y;
	size_t					x;
	t_ray					*rays;
	static t_objs			*objs;

	raytracer = (t_rt_backend_raytracer *)backend->data;
	// ray.center = first cam
	rays = rt_backend_raytracer_rays(backend, (t_vec3d){0, 0, -100}, false);
	if (!rays)
		return (NULL);
	y = 0;
	if (!objs)
		objs = tmp(); // a enlver :)
	raytracer->ticker++;
	rt_trace(backend->rt, "go banger %d\n", (int)raytracer->ticker);
	while (objs->type == CAMERA)
		objs = objs->next;
	// t_plane *plane = ((t_plane *)(objs->next->next->obj));
	// plane->normal.x += raytracer->ticker;
	while (y < backend->height)
	{
		x = 0;
		while (x < backend->width)
		{
			raytracer->buffer[y * backend->width + x] = \
				rt_backend_raytracer_one_ray(&rays[y * backend->width + x], objs);
			x++;
		}
		y++;
	}
	rt_trace(backend->rt, "banger FINI %d\n", (int)raytracer->ticker);

	return (raytracer->buffer);
}
