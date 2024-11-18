/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:31:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 21:32:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/util.h>

// stat syscall
#define SYS_STAT 0x4

long	ft_syscall(long number, ...);

int	rt_stat(const char *path, struct stat *st)
{
	return (ft_syscall(SYS_STAT, path, st));
}
