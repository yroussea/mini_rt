/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_list_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:34:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/23 00:40:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/util.h>
#include <stdlib.h>

static void	toc_list_remove_first(t_toc_list **list, t_destroy_fn *destroy)
{
	t_toc_list	*next;

	next = (*list)->next;
	if (destroy)
		destroy((*list)->data);
	free(*list);
	*list = next;
}

void	toc_list_remove(t_toc_list **list, t_toc_list *node,
				t_destroy_fn *destroy)
{
	t_toc_list	*prev;
	t_toc_list	*next;

	if (!list || !*list || !node)
		return ;
	if (*list == node)
	{
		toc_list_remove_first(list, destroy);
		return ;
	}
	prev = *list;
	next = prev->next;
	while (next)
	{
		if (next == node)
		{
			prev->next = next->next;
			if (destroy)
				destroy(next->data);
			free(next);
			return ;
		}
		prev = next;
		next = next->next;
	}
}
