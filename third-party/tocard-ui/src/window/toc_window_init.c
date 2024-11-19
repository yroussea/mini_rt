/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:01:06 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/24 02:23:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/engine.h>
#define __TOCARD_WINDOW_INTERNALS__
#include <tocard/window.h>

static inline void	toc_dispatch_event(t_toc_window *window, int event,
			int (*hook)(int, void *))
{
	const void	*mlx = window->engine->mlx;
	const void	*win = window->handle;

	mlx_on_event((void *) mlx, (void *) win, event, hook, window);
}

void	toc_window_init(t_toc_window *window)
{
	if (!window || !window->active || window->initialized)
		return ;
	toc_dispatch_event(window, MLX_WINDOW_EVENT, toc_window_event);
	toc_dispatch_event(window, MLX_KEYDOWN, toc_window_keydown);
	toc_dispatch_event(window, MLX_KEYUP, toc_window_keyup);
	toc_dispatch_event(window, MLX_MOUSEDOWN, toc_window_mousedown);
	toc_dispatch_event(window, MLX_MOUSEUP, toc_window_mouseup);
	toc_dispatch_event(window, MLX_MOUSEWHEEL, toc_window_mousewheel);
	window->initialized = true;
}
