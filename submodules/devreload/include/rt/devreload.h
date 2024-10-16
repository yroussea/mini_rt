/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devreload.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:20:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 04:02:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEVRELOAD_H
# define DEVRELOAD_H
# undef DEVRELOAD_H
# ifndef __RT_DEVRELOAD_H__
#  define __RT_DEVRELOAD_H__

#  include <rt/log.h>
#  include <rt/render/backend.h>
#  include <rt/render/frontend.h>

#  if RT_DEVRELOAD_USE_DLFCN
#   include <rt/devreload/dlfcn.h>
#   define RT_DLOPEN ft_dlopen
#   define RT_DLCLOSE ft_dlclose
#   define RT_DLSYM ft_dlsym
#   define RTLD_LAZY 0
#  else
#   include <dlfcn.h>
#   define RT_DLOPEN dlopen
#   define RT_DLCLOSE dlclose
#   define RT_DLSYM dlsym
#  endif

typedef void	(*t_devrl_load_fn)(const char *path, const char *name);

typedef struct s_rt_devrl_frontend_header
{
	const char	*name;
	void		*handle;
	void		(*destroy)(struct s_rt_frontend *self);
}	t_rt_devrl_frontend_header;

typedef struct s_rt_devrl_backend_header
{
	const char	*name;
	void		*handle;
	void		(*destroy)(struct s_rt_backend *self);
}	t_rt_devrl_backend_header;

void			rt_devrl_load_frontend(const char *path, const char *name);
void			rt_devrl_load_backend(const char *path, const char *name);

t_rt_backend	*rt_devrl_backend_setup(t_rt_backend *backend,
					t_rt_devrl_backend_header *header);
t_rt_frontend	*rt_devrl_frontend_setup(t_rt_frontend *frontend,
					t_rt_devrl_frontend_header *header);

size_t			rt_devrl_build_hidden_string(const char *path, const char *name,
					char *buffer);
void			*rt_devrl_find_symbol(void *handle, const char *symbol_name,
					const char *prefix, const char *name);

# endif // __RT_DEVRELOAD_H__
#endif // DEVRELOAD_H
