/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_load_backend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:25:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 03:53:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <rt/devreload.h>
#include <rt/render/backend.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

static t_rt_backend	*rt_devrl_backend_provider(t_rt *rt, const char *name,
				size_t width, size_t height)
{
	const char					*_devrl_path = name + ft_strlen(name) + 1;
	t_rt_devrl_backend_header	*ptr;
	t_rt_backend				*backend;

	ptr = ft_calloc(1, sizeof(t_rt_devrl_backend_header)
			+ sizeof(t_rt_backend));
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
	backend = (t_rt_backend *)(((void *)ptr)
			+ sizeof(t_rt_devrl_backend_header));
	ptr->name = name;
	backend->rt = rt;
	backend->name = name;
	backend->width = width;
	backend->height = height;
	return (rt_devrl_backend_setup(backend, ptr));
}

static void	rt_devrl_append_backend_provider(const char *hidden_str)
{
	rt_backend_provider_register((t_rt_backend_provider){
		.name = hidden_str,
		.fn = rt_devrl_backend_provider
	});
}

size_t	rt_devrl_build_hidden_string(const char *path, const char *name,
					char *buffer)
{
	size_t	len;
	char	*libname;

	libname = ft_strchr(name, '-');
	if (!libname)
		RT_DEBUG("invalid name: %s\n", name);
	if (!libname)
		exit(EXIT_FAILURE);
	libname++;
	len = ft_strlen(path) +1 + ft_strlen(name) +1 +3 + ft_strlen(name) +6 +1;
	len += ft_strlen(libname) +1;
	if (buffer)
	{
		ft_strlcpy(buffer, libname, len);
		buffer[ft_strlen(libname)] = 'a';
		ft_strlcat(buffer, path, len);
		ft_strlcat(buffer, "/", len);
		ft_strlcat(buffer, name, len);
		ft_strlcat(buffer, "/lib", len);
		ft_strlcat(buffer, name, len);
		ft_strlcat(buffer, ".rt.so", len);
		buffer[ft_strlen(libname)] = 0;
	}
	return (len);
}

void	rt_devrl_load_backend(const char *path, const char *name)
{
	size_t		len;
	char		*filepath;
	int			fd;

	len = rt_devrl_build_hidden_string(path, name, NULL);
	filepath = ft_calloc(len, sizeof(char));
	RT_DEBUG("ptr: %p\n", filepath);
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
	rt_devrl_append_backend_provider(filepath);
}
