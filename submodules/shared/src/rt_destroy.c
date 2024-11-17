/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:06:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:26:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <ft/mem.h>
#include <rt/app.h>
#include <rt/log.h>
#include <rt/objects.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <rt/util.h>

static void	rt_destroy_objects(t_obj *objects)
{
	if (objects->next)
		rt_destroy_objects(objects->next);
	rt_free_aligned(objects);
}

void	rt_destroy(t_rt *rt)
{
	if (rt->backend && rt->backend->destroy)
	{
		rt_trace(rt, "backend: %p | destroy: %p\n", rt->backend,
			rt->backend->destroy);
		rt_trace(rt, "destroying backend objects\n");
		rt_destroy_objects(rt->backend->objects);
		rt_trace(rt, "destroying backend %s\n", rt->backend->name);
		rt->backend->destroy(rt->backend);
		rt_trace(rt, "backend destroyed\n");
	}
	if (rt->frontend && rt->frontend->destroy)
	{
		rt_trace(rt, "destroying frontend %s\n", rt->frontend->name);
		rt_trace(rt, "frontend: %p | destroy: %p\n", rt->frontend,
			rt->frontend->destroy);
		rt->frontend->destroy(rt->frontend);
		rt_trace(rt, "frontend destroyed\n");
	}
	ft_memset(rt, 0, sizeof(t_rt));
}
