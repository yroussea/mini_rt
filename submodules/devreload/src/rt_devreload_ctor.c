/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devreload_ctor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:52:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:05:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>

__attribute__((constructor))
void	rt_devreload_ctor(void)
{
	RT_DEBUG("constructor for devreload called\n");
	return ;
}
