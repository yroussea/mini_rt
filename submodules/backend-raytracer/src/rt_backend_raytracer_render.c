/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_render.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:56:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:46:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/backend/raytracer.h>

t_color	rt_backend_raytracer_one_ray(t_ray *ray, t_obj *all_objs)
{
	t_obj	*obj_hit;

	obj_hit = NULL;
	if (rt_backend_raytracer_find_obj_hit(ray, all_objs, &obj_hit) != INFINITY
		&& obj_hit)
		rt_backend_raytracer_get_shading(all_objs, obj_hit, ray);
	return (ray->color);
}

#define FOV M_PI / 2

t_color	*rt_backend_raytracer_render(t_rt_backend *backend)
{
	t_rt_backend_raytracer	*raytracer;
	size_t					y;
	size_t					x;
	t_obj					*objs;

	objs = NULL;
	raytracer = (t_rt_backend_raytracer *)backend->data;
	y = 0;
	raytracer->ticker++;
	rt_trace(backend->rt, "go banger %d\n", (int)raytracer->ticker);
	while (objs->type == CAMERA)
		objs = objs->next;
	while (y < backend->height)
	{
		x = 0;
		while (x < backend->width)
		{
			raytracer->buffer[y * backend->width + x] = \
				rt_backend_raytracer_one_ray(
					&raytracer->rays[y * backend->width + x], objs);
			x++;
		}
		y++;
	}
	rt_trace(backend->rt, "banger FINI %d\n", (int)raytracer->ticker);
	return (raytracer->buffer);
}
