/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_frontend_setup.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/15 00:16:45 by kiroussa         ###   ########.fr       */
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
	rt_trace(rt, "destroying devrl backend %s\n", header->name);
	header->destroy(frontend);
	if (header->handle)
		dlclose(header->handle);
	free(header);
	rt->frontend = NULL;
	rt_trace(rt, "devrl frontend destroyed\n");
}

t_rt_frontend	*rt_devrl_frontend_setup(t_rt_frontend *frontend,
					t_rt_devrl_frontend_header *header)
{
	frontend->init = rt_devrl_find_symbol(header->handle, "init",
			"rt_frontend_", header->name);
	frontend->handoff = rt_devrl_find_symbol(header->handle, "handoff",
			"rt_frontend_", header->name);
	header->destroy = rt_devrl_find_symbol(header->handle, "destroy",
			"rt_frontend_", header->name);
	frontend->destroy = rt_devrl_destroy;
	return (frontend);
}
