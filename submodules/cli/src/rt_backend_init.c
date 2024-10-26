/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 01:26:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/app.h>
#include <rt/log.h>
#include <rt/render/backend.h>

int	rt_backend_init(t_rt *rt)
{
	t_rt_backend_provider	*provider;

	provider = rt_backend_provider_find(rt->flags.backend);
	if (provider == NULL)
	{
		rt_error(rt, "no backend provider found for '%s'\n",
			rt->flags.backend);
		return (1);
	}
	rt->backend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->backend != NULL && !rt->backend->init)
	{
		rt_error(rt, "backend provider '%s' does not have an init function\n",
			rt->flags.backend);
		return (1);
	}
	rt_trace(rt, "initializing backend\n");
	if (rt->backend == NULL || rt->backend->init(rt->backend))
	{
		rt_error(rt, "failed to initialize backend\n");
		return (1);
	}
	rt_trace(rt, "successfully initialized backend\n");
	rt->queued_frontend = rt->flags.frontend;
	return (0);
}
