/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_stop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:49:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 18:09:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/frontend/macrolibx.h>

void	rt_frontend_mlx_stop(t_rt_frontend *self)
{
	const t_rt_frontend_mlx	*frontend = (t_rt_frontend_mlx *)self->data;
	const t_toc_list		*windows = frontend->engine->windows;
	t_toc_window			*window;

	while (windows)
	{
		window = (t_toc_window *)windows->data;
		rt_trace(self->rt, "Closing window %s\n", window->name);
		toc_window_close(window);
		rt_trace(self->rt, "Window->active = %d\n", window->active);
		windows = windows->next;
	}
}
