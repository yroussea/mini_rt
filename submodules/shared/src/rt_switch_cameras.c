/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_switch_cameras.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:30:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/17 23:04:11 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/print.h"
#include "rt/objects.h"
#include <rt/render/backend.h>

void	rt_switch_camera_right(t_rt *rt, t_rt_backend *self)
{
	t_obj	*camera;

	camera = self->objects;
	ft_printf("%s %p\n", __func__, self->main_camera);
	if (!camera || !(camera->next && camera->next->type == OBJ_CAMERA))
		return ;
	while (camera && (t_camera *)camera != self->main_camera)
		camera = camera->next;
	if (!camera->next || camera->next->type != OBJ_CAMERA)
		self->main_camera = (t_camera *)self->objects;
	else
		self->main_camera = (t_camera *)camera->next;
	ft_printf("%s %p\n", __func__, self->main_camera);
	rt_backend_reload(rt);
}

void	rt_switch_camera_left(t_rt *rt, t_rt_backend *self)
{
	t_obj	*camera;
	t_obj	*prec;

	ft_printf("%s %p\n", __func__, self->main_camera);
	camera = self->objects;
	if (!camera || !(camera->next && camera->next->type == OBJ_CAMERA))
		return ;
	prec = self->objects;
	while (camera && (t_camera *)camera != self->main_camera)
	{
		prec = camera;
		camera = camera->next;
	}
	if (camera == prec)
	{
		while (prec && prec->type == OBJ_CAMERA)
			prec = prec->next;
	}
	self->main_camera = (t_camera *)prec;
	ft_printf("%s %p\n", __func__, self->main_camera);
	rt_backend_reload(rt);
}
