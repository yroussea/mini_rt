/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:15:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 03:22:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_screen_create(t_toc_screen *screen, t_toc_window *window,
				t_toc_screen_def definition, void *data)
{
	if (!screen)
		return ;
	screen->elements = NULL;
	screen->width = 0;
	screen->height = 0;
	screen->window = window;
	screen->def = definition;
	screen->data = data;
	screen->image = NULL;
	toc_screen_resize(screen, window->width, window->height);
}
