/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_chunk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:44:58 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/18 00:13:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CM_CHUNK_IMPLEMENTATION
# define CM_CHUNK_IMPLEMENTATION
#endif
#include <cmem.h>

t_cm_chunk	*cm_chunk_init(uint32_t elem_size)
{
	struct s_cm_chunk	*chunk;
	uint32_t			offset;

	chunk = malloc(sizeof(struct s_cm_chunk));
	if (chunk)
	{
		cm_memset(chunk, 0, sizeof(struct s_cm_chunk));
		offset = cm_twos_power_raise(elem_size);
		chunk->capacity = CM_CHUNK_DATA_CAP / offset;
		chunk->alignment = offset;
		chunk->elem_size = elem_size;
		if (!chunk->alignment || !chunk->capacity || offset < 8)
		{
			free(chunk);
			chunk = NULL;
		}
	}
	return (chunk);
}

void	cm_chunk_clear(t_cm_chunk *chunk_ptr, uint32_t flags)
{
	struct s_cm_chunk	*chunk;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	if (chunk->next)
		cm_chunk_clear(chunk->next, flags);
	if (!chunk)
		return ;
	if (flags & CM_CLEAR_NULL)
		cm_memset(chunk, 0, 32);
	if ((flags & CM_CLEAR_FREE) == CM_CLEAR_FREE)
		free(chunk);
}

void	*cm_chunk_alloc(t_cm_chunk *chunk_ptr)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk)
	{
		while (chunk->next)
			chunk = chunk->next;
		if (chunk->size >= chunk->capacity)
		{
			cm_chunk_link(chunk);
			chunk = chunk->next;
		}
		ptr = chunk->free_list;
		if (ptr)
			chunk->free_list = chunk->free_list->next;
		else
			ptr = &chunk->data[chunk->size * chunk->alignment];
		chunk->size++;
	}
	return (ptr);
}

void	*cm_chunk_push(t_cm_chunk *chunk_ptr, void *elem, uint32_t elem_size)
{
	struct s_cm_chunk	*chunk;
	void				*ptr;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	ptr = NULL;
	if (chunk && elem)
	{
		if (elem_size != chunk->elem_size)
			return (ptr);
		ptr = cm_chunk_alloc(chunk);
		if (ptr)
			cm_memcpy(ptr, elem, elem_size);
	}
	return (ptr);
}

void	cm_chunk_pop(t_cm_chunk *chunk_ptr, void *elem)
{
	struct s_cm_chunk	*chunk;
	uint32_t			index;

	chunk = (struct s_cm_chunk *)chunk_ptr;
	if (chunk && elem)
	{
		index = cm_chunk_index(chunk, elem);
		if (index == (uint32_t) - 1)
			return ;
		((struct s_flist *)elem)->next = chunk->free_list;
		chunk->free_list = elem;
		chunk->size--;
	}
}
