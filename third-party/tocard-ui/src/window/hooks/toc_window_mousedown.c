/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_mousedown.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:17:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 19:29:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

void	toc_propagate_mouse_to_elems(t_toc_screen *screen, int event,
	int action)
{
	const t_toc_vec2i	mouse_pos = screen->window->mouse_pos;
	t_toc_list			*node;
	t_toc_elem			*elem;

	node = screen->elements;
	while (node)
	{
		if (node->data)
		{
			elem = (t_toc_elem *) node->data;
			if (elem->enabled && elem->visible && elem->def.mouse)
				elem->def.mouse(elem, mouse_pos, event, action);
			if (!screen->window->active)
				break ;
		}
		node = node->next;
	}
}

int	toc_window_mousedown(int event, void *param)
{
	t_toc_window	*window;
	t_toc_screen	*screen;

	window = (t_toc_window *) param;
	if (!window || !window->active || !window->screen.def.id)
		return (0);
	screen = &window->screen;
	if (screen->def.mouse
		&& !screen->def.mouse(screen, window->mouse_pos, event, 1))
		return (0);
	toc_propagate_mouse_to_elems(screen, event, 1);
	return (0);
}
