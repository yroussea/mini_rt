/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_stop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:49:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 23:01:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/frontend/macrolibx.h>
# include <stdio.h>

void	rt_frontend_mlx_stop(t_rt_frontend *self)
{
	const t_rt_frontend_mlx	*frontend = (t_rt_frontend_mlx *)self->data;
	const t_toc_list		*windows = frontend->engine->windows;
	t_toc_window			*window;

	while (windows)
	{
		window = (t_toc_window *)windows->data;
		printf("Closing window %s\n", window->name);
		toc_window_close(window);
		printf("window->active = %d\n", window->active);
		fflush(stdout);
		windows = windows->next;
	}
}
