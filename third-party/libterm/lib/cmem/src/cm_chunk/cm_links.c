/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_links.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:03:50 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/18 00:13:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_next(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	return (chunk->next);
}

void	cm_chunk_link(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	chunk->next = cm_chunk_init(chunk->alignment);
}

uint32_t	cm_chunk_size(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	uint32_t			size;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	size = 0;
	while (chunk)
	{
		size += chunk->size;
		chunk = chunk->next;
	}
	return (size);
}
