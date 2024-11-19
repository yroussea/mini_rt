/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_elem_is_hovered.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:33:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 02:38:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>

bool	toc_elem_is_hovered(t_toc_elem *elem, t_toc_vec2i mouse_pos)
{
	const int	x = mouse_pos.x;
	const int	y = mouse_pos.y;

	return (x >= elem->x && x < elem->x + (int) elem->width
		&& y >= elem->y && y < elem->y + (int) elem->height);
}
