/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:21:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 21:33:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H
# undef UTIL_H
# ifndef __RT_UTIL_H__
#  define __RT_UTIL_H__

#  include <stdarg.h>
#  include <stddef.h>
#  include <stdint.h>
#  include <sys/stat.h>

void	*rt_malloc_aligned(size_t size, size_t alignment);
void	rt_free_aligned(void *ptr);

struct	s_syscall_args
{
	uint64_t	rax;
	uint64_t	rdi;
	uint64_t	rsi;
	uint64_t	rdx;
	uint64_t	r10;
	uint64_t	r8;
	uint64_t	r9;
};

long	ft_syscall(long number, ...);
int		rt_stat(const char *path, struct stat *buf);

# endif // __RT_UTIL_H__
#endif // UTIL_H
