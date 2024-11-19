/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:50:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/13 15:26:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __TOCARD_WINDOW_INTERNALS__
#include <tocard/window.h>

int	toc_window_event(int event, void *param)
{
	t_toc_window	*window;

	window = (t_toc_window *) param;
	if (!window)
		return (0);
	if (event == 0)
		toc_window_close(window);
	if (event == 5)
		window->focused = 1;
	if (event == 7)
		window->focused = 0;
	if (event == 4)
		window->hovered = 1;
	if (event == 6)
		window->hovered = 0;
	return (0);
}
