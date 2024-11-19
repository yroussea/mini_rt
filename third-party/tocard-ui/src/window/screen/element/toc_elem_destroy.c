/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_elem_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:11:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 03:22:43 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>
#include <stdlib.h>

void	toc_elem_destroy(t_toc_elem *elem)
{
	if (!elem)
		return ;
	if (elem->def.destroy)
		elem->def.destroy(elem);
	free(elem);
}
