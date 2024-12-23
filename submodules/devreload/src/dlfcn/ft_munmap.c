/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_munmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:09:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 21:35:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/util.h>
#define __RT_DEVRELOAD_DLFCN_INTERNAL__
#include <rt/devreload/dlfcn.h>

int	ft_munmap(void *addr, size_t len)
{
	int	ret;

	ret = ft_syscall(SYS_MUNMAP, addr, len);
	if (ret == -1)
		return (-1);
	return (0);
}
