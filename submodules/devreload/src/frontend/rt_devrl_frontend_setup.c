/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_frontend_setup.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 06:06:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/devreload.h>
#include <stdlib.h>

static void	rt_devrl_destroy(t_rt_frontend *frontend)
{
	t_rt_devrl_frontend_header	*header;
	t_rt						*rt;

	header = (t_rt_devrl_frontend_header *)((void *)frontend
			- sizeof(t_rt_devrl_frontend_header));
	if (!header)
		return ;
	rt = frontend->rt;
	rt_trace(rt, "devrl: destroying backend %s\n", header->name);
	header->destroy(frontend);
	if (header->handle)
		RT_DLCLOSE(header->handle);
	free(header);
	rt->frontend = NULL;
	rt_trace(rt, "devrl: frontend destroyed\n");
}

t_rt_frontend	*rt_devrl_frontend_setup(t_rt_frontend *frontend,
					t_rt_devrl_frontend_header *header)
{
	frontend->init = rt_devrl_find_symbol(header->handle, "init",
			"rt_frontend_", header->name);
	rt_trace(frontend->rt, "devrl: frontend %s init: %p\n", header->name,
		frontend->init);
	frontend->handoff = rt_devrl_find_symbol(header->handle, "handoff",
			"rt_frontend_", header->name);
	rt_trace(frontend->rt, "devrl: frontend %s handoff: %p\n", header->name,
		frontend->handoff);
	frontend->stop = rt_devrl_find_symbol(header->handle, "stop",
			"rt_frontend_", header->name);
	rt_trace(frontend->rt, "devrl: frontend %s stop: %p\n", header->name,
		frontend->stop);
	header->destroy = rt_devrl_find_symbol(header->handle, "destroy",
			"rt_frontend_", header->name);
	rt_trace(frontend->rt, "devrl: frontend %s destroy: %p\n", header->name,
		header->destroy);
	frontend->destroy = rt_devrl_destroy;
	return (frontend);
}
