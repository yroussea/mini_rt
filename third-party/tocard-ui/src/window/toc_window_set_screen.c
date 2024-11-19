/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_set_screen.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:45:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:27:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/defaults.h>
#include <tocard/window.h>

void	toc_window_set_screen(t_toc_window *window, t_toc_screen_def definition,
			void *data)
{
	if (!window)
		return ;
	toc_screen_destroy(&window->screen);
	toc_screen_create(&window->screen, window, definition, data);
	if (window->screen.def.init)
		window->screen.def.init(&window->screen);
}
