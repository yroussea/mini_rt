/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:22:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/13 15:25:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

#include <stdio.h>

static inline void	toc_elem_update(t_toc_elem *elem, t_toc_vec2i mouse_pos)
{
	if (elem->def.render)
		elem->def.render(elem, mouse_pos);
}

static inline void	toc_window_update_mouse(t_toc_window *window)
{
	int	mouse_x;
	int	mouse_y;

	if (window->hovered)
	{
		mlx_mouse_get_pos(window->engine->mlx, &mouse_x, &mouse_y);
		window->mouse_pos = (t_toc_vec2i){mouse_x, mouse_y};
	}
}

void	toc_window_update(t_toc_window *window)
{
	t_toc_list	*node;

	if (!window)
		return ;
	mlx_clear_window(window->engine->mlx, window->handle);
	toc_window_update_mouse(window);
	if (window->screen.def.render)
	{
		if (window->screen.def.render(&window->screen, window->mouse_pos))
		{
			node = window->screen.elements;
			while (node)
			{
				if (node->data)
					toc_elem_update((t_toc_elem *) node->data,
						window->mouse_pos);
				node = node->next;
			}
		}
	}
	mlx_put_image_to_window(window->engine->mlx, window->handle,
		window->screen.image, 0, 0);
}
