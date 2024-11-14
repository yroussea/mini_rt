/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_malloc_aligned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:37:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/14 21:58:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <stdint.h>

/**
 * To allocate aligned memory, we setup:
 * [ Padding [ Size header ]] | [ Aligned Data ]
 */
void	*rt_malloc_aligned(size_t size, size_t alignment)
{
	void	*ptr;
	size_t	offset;

	ptr = ft_calloc(1, sizeof(size_t) + size + alignment);
	if (!ptr)
		return (NULL);
	offset = 0;
	ptr += sizeof(size_t);
	while ((uintptr_t)ptr % alignment != 0)
	{
		ptr++;
		offset++;
	}
	ptr -= sizeof(size_t);
	*(size_t *)ptr = offset;
	ptr += sizeof(size_t);
	return (ptr);
}
