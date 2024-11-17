/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_backend_setup.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:40:37 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 22:50:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/devreload.h>
#include <stdlib.h>

void	*rt_devrl_find_symbol(void *handle, const char *symbol_name,
				const char *prefix, const char *name)
{
	char			*symbol;
	const size_t	len = ft_strlen(prefix) + ft_strlen(name)
		+ ft_strlen(symbol_name) + 2;
	void			*ptr;

	symbol = ft_calloc(len, sizeof(char));
	if (!symbol)
		return (NULL);
	ft_strlcpy(symbol, prefix, len);
	ft_strlcat(symbol, name, len);
	ft_strlcat(symbol, "_", len);
	ft_strlcat(symbol, symbol_name, len);
	ptr = RT_DLSYM(handle, symbol);
	free(symbol);
	return (ptr);
}

static void	rt_devrl_destroy(t_rt_backend *backend)
{
	t_rt_devrl_backend_header	*header;
	t_rt						*rt;

	header = (t_rt_devrl_backend_header *)((void *)backend
			- sizeof(t_rt_devrl_backend_header));
	if (!header)
		return ;
	rt = backend->rt;
	rt_trace(rt, "devrl: destroying backend %s\n", header->name);
	header->destroy(backend);
	if (header->handle)
		RT_DLCLOSE(header->handle);
	free(header);
	rt_trace(rt, "devrl: backend destroyed\n");
}

t_rt_backend	*rt_devrl_backend_setup(t_rt_backend *backend,
					t_rt_devrl_backend_header *header)
{
	backend->init = rt_devrl_find_symbol(header->handle, "init",
			"rt_backend_", header->name);
	rt_trace(backend->rt, "devrl: backend %s init: %p\n", header->name,
		backend->init);
	backend->update = rt_devrl_find_symbol(header->handle, "update",
			"rt_backend_", header->name);
	rt_trace(backend->rt, "devrl: backend %s update: %p\n", header->name,
		backend->update);
	backend->render = rt_devrl_find_symbol(header->handle, "render",
			"rt_backend_", header->name);
	rt_trace(backend->rt, "devrl: backend %s render: %p\n", header->name,
		backend->render);
	header->destroy = rt_devrl_find_symbol(header->handle, "destroy",
			"rt_backend_", header->name);
	rt_trace(backend->rt, "devrl: backend %s destroy: %p\n", header->name,
		header->destroy);
	backend->destroy = &rt_devrl_destroy;
	return (backend);
}
