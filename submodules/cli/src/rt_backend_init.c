/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:15:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/cli.h>
#include <rt/log.h>
#include <rt/render/backend.h>

#define ERROR_NO_PROVIDER "no backend provider found for '%s'\n"
#define ERROR_NO_BACKEND "backend provider '%s' does not have a backend\n"
#define ERROR_NO_INIT "backend provider '%s' does not have an init function\n"
#define ERROR_INIT_FAILED "failed to initialize backend\n"

static t_obj	*rt_object_list(t_list *objects)
{
	t_obj	*obj;
	t_obj	*tmp;

	if (!objects)
		return (NULL);
	obj = (t_obj *)objects->content;
	tmp = obj;
	while (objects->next)
	{
		objects = objects->next;
		tmp->next = (t_obj *)objects->content;
		tmp = tmp->next;
	}
	return (obj);
}

int	rt_backend_init(t_rt *rt, t_list *objects)
{
	t_rt_backend_provider	*provider;

	provider = rt_backend_provider_find(rt->flags.backend);
	if (provider == NULL)
		rt_error(rt, ERROR_NO_PROVIDER, rt->flags.backend);
	if (provider == NULL)
		return (1);
	rt->backend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->backend == NULL)
		rt_error(rt, ERROR_NO_BACKEND, provider->name);
	else if (!rt->backend->init)
		rt_error(rt, ERROR_NO_INIT, provider->name);
	if (rt->backend == NULL || !rt->backend->init)
		return (2 + rt->backend != NULL);
	rt_trace(rt, "initializing backend\n");
	rt->backend->objects = rt_object_list(objects);
	if (rt->backend->init(rt->backend))
	{
		rt_error(rt, ERROR_INIT_FAILED);
		return (4);
	}
	rt_trace(rt, "successfully initialized backend\n");
	rt->queued_frontend = rt->flags.frontend;
	return (0);
}
