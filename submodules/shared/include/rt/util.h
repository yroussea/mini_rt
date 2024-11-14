/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:21:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:21:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# undef UTIL_H
# ifndef __RT_UTIL_H__
#  define __RT_UTIL_H__

#  include <stddef.h>

void	*rt_malloc_aligned(size_t size, size_t alignment);
void	rt_free_aligned(void *ptr);

# endif // __RT_UTIL_H__
#endif // UTIL_H
