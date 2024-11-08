/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_free_aligned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:42:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>

void	rt_free_aligned(void *ptr)
{
	size_t	*size_ptr;

	if (!ptr)
		return ;
	size_ptr = (size_t *)(ptr - sizeof(size_t));
	ptr -= sizeof(size_t) + *size_ptr;
	free(ptr);
}
