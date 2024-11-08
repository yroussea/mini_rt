/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 18:30:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#include <rt/render/backend/raytracer.h>

static bool	rt_backend_raytracer_init_rays(t_rt_backend *self,
				t_vec3d center, t_rt_backend_raytracer *raytracer)
{
	const int	width = self->width;
	const int	height = self->height;
	int			i;

	raytracer->rays = ft_calloc(width * height + 64, sizeof(t_ray));
	while (raytracer->rays && ((uintptr_t)raytracer->rays) % 32 != 0)
	{
		raytracer->rays = (t_ray *)((uintptr_t)raytracer->rays + 1);
		raytracer->rays_alignment_offset++;
	}
	if (!raytracer->rays)
		return (false);
	i = 0;
	while (i < width * height)
	{
		raytracer->rays[i].center = center;
		eye_rays(&raytracer->rays[i], get_width(self, i % width),
			get_height(self, i / width), 90); //FIXME: fov
		i++;
	}
	return (true);
}

int	rt_backend_raytracer_init(t_rt_backend *self)
{
	t_rt_backend_raytracer	*data;

	rt_trace(self->rt, "initializing raytracer backend\n");
	data = ft_calloc(1, sizeof(t_rt_backend_raytracer));
	if (!data)
		return (1);
	self->data = data;
	data->buffer = ft_calloc(self->width * self->height, sizeof(t_color));
	if (!data->buffer)
		return (1);
	// ray.center = first cam
	if (!rt_backend_raytracer_init_rays(self, (t_vec3d){0, 0, -100}, data))
		return (1);
	return (0);
}
