/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_stop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:49:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 23:43:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/frontend/macrolibx.h>

void	rt_frontend_mlx_stop(t_rt_frontend *self)
{
	const t_rt_frontend_mlx	*frontend = (t_rt_frontend_mlx *)self->data;
	const t_toc_list		*windows = frontend->engine->windows;

	while (windows)
	{
		toc_window_close(windows->data);
		windows = windows->next;
	}
}
