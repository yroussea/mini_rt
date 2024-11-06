/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_switch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:05:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 20:01:59 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/backend.h>

void	rt_backend_switch(t_rt *rt, const char *name)
{
	t_rt_backend_provider	*provider;

	provider = rt_backend_provider_find(name);
	if (provider == NULL)
	{
		rt_error(rt, "no backend provider found for %s\n", name);
		return ;
	}
	rt_trace(rt, "switching backend to %s\n", name);
	if (rt->backend->destroy)
		rt->backend->destroy(rt->backend);
	rt->backend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (!rt->backend)
		rt_error(rt, "failed to create backend\n");
	else if (rt->backend->init)
		rt->backend->init(rt->backend);
	rt_trace(rt, "switch complete\n");
}
