/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 03:38:54 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 23:31:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/cli.h>
#include <rt/log.h>
#include <rt/render/backend.h>

#define ERROR_NO_PROVIDER "no backend provider found for '%s'\n"
#define ERROR_NO_BACKEND "backend provider '%s' does not have a backend\n"
#define ERROR_NO_INIT "backend provider '%s' does not have an init function\n"
#define ERROR_INIT_FAILED "failed to initialize backend\n"

static void	rt_add_object_order(t_obj **objs, t_obj *new)
{
	t_obj	*tmp;

	tmp = *objs;
	while (tmp && tmp->next && tmp->next->type < new->type)
		tmp = tmp->next;
	if (tmp && tmp->type < new->type)
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	else
	{
		new->next = tmp;
		*objs = new;
	}
}

t_obj	*rt_object_list(t_list *objects)
{
	t_obj	*obj;

	obj = NULL;
	while (objects)
	{
		rt_add_object_order(&obj, objects->content);
		objects = objects->next;
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
