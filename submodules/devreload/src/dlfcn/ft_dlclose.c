/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlclose.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:05:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:23:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_DEVRELOAD_DLFCN_INTERNAL__
#include <rt/devreload/dlfcn.h>
#include <stdlib.h>

int	ft_dlclose(void *handle)
{
	t_dl_info	*dl_info;

	dl_info = (t_dl_info *)handle;
	if (dl_info && dl_info->start)
		return (ft_munmap(dl_info->start, dl_info->size));
	if (dl_info)
		free(dl_info);
	return (0);
}
