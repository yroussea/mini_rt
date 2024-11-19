/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_mouseup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:17:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 19:28:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_propagate_mouse_to_elems(t_toc_screen *screen, int event,
			int action);

int	toc_window_mouseup(int event, void *param)
{
	t_toc_window	*window;
	t_toc_screen	*screen;

	window = (t_toc_window *) param;
	if (!window || !window->active || !window->screen.def.id)
		return (0);
	screen = &window->screen;
	if (screen->def.mouse
		&& !screen->def.mouse(screen, window->mouse_pos, event, 0))
		return (0);
	toc_propagate_mouse_to_elems(screen, event, 0);
	return (0);
}
