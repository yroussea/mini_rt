/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cm_chunk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 00:36:49 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/18 00:13:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CM_CHUNK_H
# define CM_CHUNK_H

# include <stdint.h>

# define CM_CHUNK_DATA_CAP	4032

/* ************************************************************************** */

/**
 * @struct	s_cm_iter		Describes a memroy chunk iterator
 *
 * @void *		(it)		Pointer to the current element.
 * @void *		(start)		Start iterator, points to the start of chunk->data.
 * @void *		(end)		End iterator, points to the last element adress.
 * @uint32_t	(index)		Index of the current element.
 */
struct s_cm_iter
{
	void		*it;
	void		*start;
	void		*end;
	uint32_t	index;
};

/**
 * @struct	s_chunk			Describes a memory chunk
 *
 * @uint32_t	(capacity)	Maximum capacity of the chunk.
 * @uint32_t	(size)		Actual size of the chunk.
 * @uint32_t	(alignment)	Alignment factor of the concerned data.
 * @uint32_t	(elem_size)	Element size.
 */
struct s_cm_chunk
{
	uint32_t			capacity;
	uint32_t			size;
	uint32_t			alignment;
	uint32_t			elem_size;
	struct s_flist		*free_list;
	struct s_cm_iter	iterator;
	struct s_cm_chunk	*next;
	uint8_t				data[CM_CHUNK_DATA_CAP];
};

/* ************************************************************************** */

#endif
