/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_load_frontend.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:25:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:54:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <rt/devreload.h>
#include <rt/render/frontend.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static t_rt_frontend	*rt_devrl_frontend_provider(t_rt *rt, const char *name,
				size_t width, size_t height)
{
	const char					*_devrl_path = name + ft_strlen(name) + 1;
	t_rt_devrl_frontend_header	*ptr;
	t_rt_frontend				*frontend;

	ptr = ft_calloc(1, sizeof(t_rt_devrl_frontend_header)
			+ sizeof(t_rt_frontend));
	if (!ptr)
		return (NULL);
	ptr->handle = RT_DLOPEN(_devrl_path, RTLD_LAZY);
	if (!ptr->handle)
	{
		RT_DEBUG("dlopen error: %m\n");
		free((void *) name);
		free(ptr);
		return (NULL);
	}
	frontend = (t_rt_frontend *)(((void *)ptr)
			+ sizeof(t_rt_devrl_frontend_header));
	ptr->name = name;
	frontend->rt = rt;
	frontend->name = name;
	frontend->width = width;
	frontend->height = height;
	return (rt_devrl_frontend_setup(frontend, ptr));
}

static void	rt_devrl_append_frontend_provider(const char *hidden_str)
{
	rt_frontend_provider_register((t_rt_frontend_provider){
		.name = hidden_str,
		.fn = rt_devrl_frontend_provider
	});
}

void	rt_devrl_load_frontend(const char *path, const char *name)
{
	size_t		len;
	char		*filepath;
	int			fd;

	len = rt_devrl_build_hidden_string(path, name, NULL);
	filepath = ft_calloc(len, sizeof(char));
	if (!filepath)
	{
		RT_DEBUG("malloc error\n");
		exit(EXIT_FAILURE);
	}
	rt_devrl_build_hidden_string(path, name, filepath);
	RT_DEBUG("load '%s' from '%s'\n", filepath,
		filepath + ft_strlen(filepath) + 1);
	fd = open(filepath + ft_strlen(filepath) + 1, O_RDONLY);
	if (fd == -1)
	{
		RT_DEBUG("open error: %m\n");
		free(filepath);
		exit(EXIT_FAILURE);
	}
	close(fd);
	rt_devrl_append_frontend_provider(filepath);
}
