/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_list_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:15:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/23 00:40:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/util.h>
#include <stdlib.h>

void	toc_list_clear(t_toc_list **list, t_destroy_fn *destroy)
{
	t_toc_list	*node;
	t_toc_list	*next;

	if (!list || !*list)
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		if (destroy && node->data)
			destroy(node->data);
		free(node);
		node = next;
	}
	*list = NULL;
}
