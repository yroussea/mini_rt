/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:54:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 08:27:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_window_close(t_toc_window *window)
{
	if (!window || !window->active)
		return ;
	window->active = false;
	toc_screen_destroy(&window->screen);
	mlx_destroy_window(window->engine->mlx, window->handle);
}
