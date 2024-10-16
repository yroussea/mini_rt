/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:59:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:32:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_DEVRELOAD_DLFCN_INTERNAL__
#include <rt/devreload/dlfcn.h>

static void	*ft_mmap_impl(void *addr, size_t len, int flags_arr[3], off_t off)
{
	const int	prot = flags_arr[0];
	const int	flags = flags_arr[1];
	const int	fd = flags_arr[2];
	const void	*ret = (void *)ft_syscall(SYS_MMAP, addr, len, prot, flags,
			fd, off);

	if (ret == (void *)-1)
		return (NULL);
	return ((void *)ret);
}

void	*ft_mmap(void *addr, ...)
{
	va_list	ap;
	size_t	len;
	int		flags[3];
	off_t	off;

	va_start(ap, addr);
	len = va_arg(ap, size_t);
	flags[0] = va_arg(ap, int);
	flags[1] = va_arg(ap, int);
	flags[2] = va_arg(ap, int);
	off = va_arg(ap, off_t);
	va_end(ap);
	return (ft_mmap_impl(addr, len, flags, off));
}
