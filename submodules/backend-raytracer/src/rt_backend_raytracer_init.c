/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 07:24:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include "ft/math.h"
#include "rt/objects.h"
#include <ft/mem.h>
#include <math.h>
#include <rt/log.h>
#include <rt/render/backend/raytracer.h>

static void	rt_backend_raytracer_update_camera_angle(t_camera *cam)
{
	const t_vec3d	v = v3d_norm(&cam->view_vector);

	cam->theta = acos(v.y);
	cam->phi = ft_fsign(v.z) * acos(v.x / sqrt(v.x * v.x + v.z * v.z));
}

static bool	rt_backend_raytracer_init_rays(t_rt_backend *self,
				t_camera *cam, t_rt_backend_raytracer *raytracer)
{
	const int		width = self->width;
	const int		height = self->height;
	const t_mat3d	rotation = m3d_rot(cam->theta, cam->phi, 0);
	int				i;

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
		raytracer->rays[i].center = cam->point;
		rt_backend_raytracer_init_ray(&raytracer->rays[i], \
			rt_backend_raytracer_get_rays_relative_coo(self, i % width, \
			(float)i / width, cam->fov), &rotation);
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
	rt_backend_raytracer_update_camera_angle((t_camera *)data->objs);
	if (!rt_backend_raytracer_init_rays(self, (t_camera *)data->objs, data))
		return (1);
	return (0);
}
