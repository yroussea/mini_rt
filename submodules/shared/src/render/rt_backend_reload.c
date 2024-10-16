/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_reload.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:11:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 06:59:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

#if RT_DEVMODE
# include <rt/devreload.h>

void	rt_backend_reload(t_rt *rt)
{
	rt_devrl_recompile(rt);
	rt_backend_switch(rt, rt->backend->name);
}

#else

void	rt_backend_reload(t_rt *rt)
{
	rt_backend_switch(rt, rt->backend->name);
}

#endif
