/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:53:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 18:26:55 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/frontend/macrolibx.h>

int	rt_frontend_mlx_init(t_rt_frontend *self)
{
	t_rt_frontend_mlx	*data;

	self->flags = FRONTEND_SUPPORT_UI | FRONTEND_SUPPORT_KEYBOARD
		| FRONTEND_SUPPORT_MOUSE | FRONTEND_SUPPORT_RESIZE;
	data = ft_calloc(1, sizeof(t_rt_frontend_mlx));
	if (!data)
		return (1);
	self->data = data;
	data->engine = toc_engine_create();
	if (!data->engine)
		return (1);
	data->main_window = toc_window_create(data->engine, self->rt->name,
			self->width, self->height);
	if (!data->main_window)
		return (1);
	toc_window_set_screen(data->main_window, rt_screen_main(), self);
	return (0);
}
