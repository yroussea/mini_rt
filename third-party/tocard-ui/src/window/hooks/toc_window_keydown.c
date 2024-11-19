/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_keydown.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:16:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:09:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_propagate_key_to_elems(t_toc_screen *screen, int event,
	int state, int last_state)
{
	t_toc_list	*node;
	t_toc_elem	*elem;

	node = screen->elements;
	while (node)
	{
		if (node->data)
		{
			elem = (t_toc_elem *) node->data;
			if (elem->enabled && elem->visible && elem->def.key)
				elem->def.key(elem, event, state, last_state);
			if (!screen->window->active)
				break ;
		}
		node = node->next;
	}
}

int	toc_window_keydown(int event, void *param)
{
	t_toc_window	*window;
	t_toc_screen	*screen;
	int				last_state;

	window = (t_toc_window *) param;
	if (!window || !window->active || !window->screen.def.id)
		return (0);
	screen = &window->screen;
	last_state = window->keymap[event];
	window->keymap[event] = 1;
	if (screen->def.key
		&& !screen->def.key(screen, event, 1, last_state))
		return (0);
	toc_propagate_key_to_elems(screen, event, 1, last_state);
	return (0);
}
