/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 20:56:22 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/app.h>
#include <rt/log.h>
#include <rt/render/frontend.h>

#define ERROR_NO_INIT "frontend provider '%s' does not have an init function\n"

int	rt_frontend_init(t_rt *rt)
{
	t_rt_frontend_provider	*provider;

	rt_trace(rt, "initializing frontend '%s'\n", rt->queued_frontend);
	provider = rt_frontend_provider_find(rt->queued_frontend);
	if (provider == NULL)
	{
		rt_error(rt, "no frontend provider found for '%s'\n",
			rt->queued_frontend);
		return (1);
	}
	rt->queued_frontend = NULL;
	rt->frontend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->frontend != NULL && !rt->frontend->init)
		rt_error(rt, ERROR_NO_INIT, provider->name);
	if (rt->frontend != NULL && !rt->frontend->init)
		return (1);
	rt_trace(rt, "calling frontend initialization function...\n");
	if (rt->frontend == NULL || rt->frontend->init(rt->frontend))
	{
		rt_error(rt, "failed to initialize frontend\n");
		return (1);
	}
	rt_trace(rt, "initialized frontend\n");
	return (0);
}
