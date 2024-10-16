/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_switch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:05:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 06:22:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/frontend.h>

void	rt_frontend_switch(t_rt *rt, const char *name)
{
	t_rt_frontend_provider	*provider;

	if (rt->frontend && !(rt->frontend->flags & FRONTEND_SUPPORT_RESIZE))
	{
		rt_warn(rt, "switching frontends at runtime is not supported yet; "
			"use the -f CLI flag to specify the frontend to use\n");
		return ;
	}
	provider = rt_frontend_provider_find(name);
	if (provider == NULL)
	{
		rt_error(rt, "no frontend provider found for %s", name);
		return ;
	}
	rt_trace(rt, "switching frontend to %s", name);
	if (rt->frontend && rt->frontend->stop)
		rt->frontend->stop(rt->frontend);
	rt->queued_frontend = name;
}
