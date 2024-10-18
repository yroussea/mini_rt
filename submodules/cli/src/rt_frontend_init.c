/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:12 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:39:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/app.h>
#include <rt/log.h>
#include <rt/render/frontend.h>

int	rt_frontend_init(t_rt *rt)
{
	t_rt_frontend_provider	*provider;

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
	{
		rt_error(rt, "frontend provider '%s' does not have an init function\n",
			provider->name);
		return (1);
	}
	if (rt->frontend == NULL || rt->frontend->init(rt->frontend))
	{
		rt_error(rt, "failed to initialize frontend\n");
		return (1);
	}
	return (0);
}
