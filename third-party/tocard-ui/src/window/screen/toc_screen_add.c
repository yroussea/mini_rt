/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:04:30 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/12 16:14:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>
#include <tocard/util.h>

void	toc_screen_add(t_toc_screen *screen, t_toc_elem *element)
{
	t_toc_list	*node;

	if (!screen || !element)
		return ;
	element->screen = screen;
	node = toc_list_create(element);
	if (!node)
	{
		toc_elem_destroy(element);
		return ;
	}
	toc_list_push(&screen->elements, node);
	if (element->def.init)
		element->def.init(element);
}
