/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_render.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:56:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 20:52:04 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//pixelisation!!
t_objs	*tmp()
{
	return (plane((t_vec3d){0.5, 1, 0}, (t_vec3d){0, -20, 0}, (t_vec3d){0.2, 0.2, 0.2}));
}

t_color	*rt_backend_raytracer_render(t_rt_backend *backend)
{
	const t_rt_backend_raytracer	*raytracer
		= (t_rt_backend_raytracer *)backend->data;
	size_t	y;
	size_t	x;
	t_ray	ray;
	t_objs	*objs = NULL;

	y = 0;
	objs = tmp();
	objs->next = NULL;
	// ray.center = first cam
	ray.center = (t_vec3d){0, 0, -100};
	while (y < backend->height)
	{
		x = 0;
		while (x < backend->width)
		{
			eye_rays(&ray, get_width(backend, x, /*fov*/ 90), get_height(backend, y));
			raytracer->buffer[y * backend->width + x] = \
				rt_backend_raytracer_one_ray(ray, objs);
			x++;
		}
		y++;
	}
	return (raytracer->buffer);
}
