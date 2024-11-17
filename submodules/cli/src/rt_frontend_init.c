/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:14:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/app.h>
#include <rt/log.h>
#include <rt/render/frontend.h>

#define ERROR_NO_PROVIDER "no frontend provider found for '%s'\n"
#define ERROR_NO_FRONTEND "frontend provider '%s' does not have a frontend\n"
#define ERROR_NO_INIT "frontend provider '%s' does not have an init function\n"
#define ERROR_INIT_FAILED "failed to initialize frontend\n"

int	rt_frontend_init(t_rt *rt)
{
	t_rt_frontend_provider	*provider;

	rt_trace(rt, "initializing frontend '%s'\n", rt->queued_frontend);
	provider = rt_frontend_provider_find(rt->queued_frontend);
	if (provider == NULL)
	{
		rt_error(rt, ERROR_NO_PROVIDER, rt->queued_frontend);
		return (1);
	}
	rt->queued_frontend = NULL;
	rt->frontend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->frontend == NULL)
		rt_error(rt, ERROR_NO_FRONTEND, provider->name);
	else if (!rt->frontend->init)
		rt_error(rt, ERROR_NO_INIT, provider->name);
	if (rt->frontend == NULL || !rt->frontend->init)
		return (2 + rt->frontend != NULL);
	rt_trace(rt, "calling frontend initialization function...\n");
	if (rt->frontend == NULL || rt->frontend->init(rt->frontend))
	{
		rt_error(rt, ERROR_INIT_FAILED);
		return (4);
	}
	rt_trace(rt, "initialized frontend\n");
	return (0);
}
