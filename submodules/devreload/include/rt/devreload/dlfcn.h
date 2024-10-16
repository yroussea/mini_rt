/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlfcn.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:44:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:53:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLFCN_H
# define DLFCN_H
# undef DLFCN_H
# ifndef __RT_DEVRELOAD_DLFCN_H
#  define __RT_DEVRELOAD_DLFCN_H

#  ifndef DLFCN_VERBOSE
#   error "DLFCN_VERBOSE is not defined"
#   ifdef RT_DEBUG
#    undef RT_DEBUG
#   endif // RT_DEBUG
#  endif // DLFCN_VERBOSE
#  include <rt/log.h>

#  include <fcntl.h>
#  include <stdarg.h>
#  include <stddef.h>
#  include <stdint.h>
#  include <sys/mman.h>
#  include <unistd.h>

void	*ft_dlopen(const char *path, int ignored);
void	*ft_dlsym(void *handle, const char *symbol);
int		ft_dlclose(void *handle);

#  ifdef __RT_DEVRELOAD_DLFCN_INTERNAL__

typedef struct s_dl_info
{
	void	*start;
	size_t	size;
}	t_dl_info;

void	*ft_mmap(void *addr, ...);
int		ft_munmap(void *addr, size_t len);

#   define SYS_MMAP			9
#   define SYS_MUNMAP		11

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

#  endif

# endif // __RT_DEVRELOAD_DLFCN_H
#endif // DLFCN_H
