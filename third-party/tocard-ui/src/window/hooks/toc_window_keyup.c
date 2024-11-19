/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_keyup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:10:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_propagate_key_to_elems(t_toc_screen *screen, int event,
			int state, int last_state);

int	toc_window_keyup(int event, void *param)
{
	t_toc_window	*window;
	t_toc_screen	*screen;
	int				last_state;

	window = (t_toc_window *) param;
	if (!window || !window->active || !window->screen.def.id)
		return (0);
	screen = &window->screen;
	last_state = window->keymap[event];
	window->keymap[event] = 0;
	if (screen->def.key
		&& !screen->def.key(screen, event, 0, last_state))
		return (0);
	toc_propagate_key_to_elems(screen, event, 0, last_state);
	return (0);
}
