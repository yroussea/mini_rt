/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 18:35:45 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/mem.h>
#include <math.h>
#include <rt/log.h>
#include <rt/render/backend/raytracer.h>

t_vec3d	rt_backend_raytracing_lights_colors(
	__attribute__((unused))const t_ray *ray, t_light *obj)
{
	return (obj->base.material.colors);
}

static void	rt_backend_raytracer_update_camera_angle(t_obj *obj)
{
	t_camera	*cam;
	t_vec3d		v;

	cam = (t_camera *)obj;
	v = v3d_norm(&cam->view_vector);
	if (cam->convet_done)
		return ;
	cam->convet_done = 1;
	cam->theta = acos(v.y) - M_PI / 2;
	cam->phi = ft_fsign(v.z) * acos(v.x / sqrt(v.x * v.x + v.z * v.z));
	cam->phi -= M_PI / 2;
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
			(float)i / width, cam->fov * M_PI / 180), &rotation);
		i++;
	}
	return (true);
}

static void	rt_backend_raytracer_init_objects(t_rt_backend *self)
{
	t_obj		*objs;
	static void	(*init_obj[_OBJ_SIZE])(t_obj *obj) = {
		NULL, rt_backend_raytracer_update_camera_angle, NULL, NULL,
		rt_backend_raytracer_sphere, rt_backend_raytracer_plane,
		rt_backend_raytracer_cylinder, rt_backend_raytracer_cone};

	objs = self->objects;
	while (objs)
	{
		if (init_obj[objs->type])
			init_obj[objs->type](objs);
		else if (objs->type != OBJ_UNKNOWN)
			objs->calc_color = rt_backend_raytracing_lights_colors;
		objs = objs->next;
	}
}

int	rt_backend_raytracer_init(t_rt_backend *self)
{
	t_rt_backend_raytracer	*data;

	rt_trace(self->rt, "initializing raytracer backend (%p)\n", self);
	data = ft_calloc(1, sizeof(t_rt_backend_raytracer));
	if (!data)
		return (1);
	self->data = data;
	data->buffer = ft_calloc(self->width * self->height, sizeof(t_color));
	if (!data->buffer)
		return (1);
	if (!self->objects)
	{
		rt_error(self->rt, "no objects\n");
		return (1);
	}
	rt_backend_raytracer_init_objects(self);
	if (!self->main_camera)
		self->main_camera = (t_camera *)self->objects;
	if (!rt_backend_raytracer_init_rays(self, self->main_camera, data))
	{
		rt_error(self->rt, "no init rays\n");
		return (1);
	}
	return (0);
}
