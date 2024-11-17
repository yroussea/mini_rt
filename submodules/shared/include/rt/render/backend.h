/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:57:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:12:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H
# undef BACKEND_H
# ifndef __RT_RENDER_BACKEND_H__
#  define __RT_RENDER_BACKEND_H__

#  include <rt/app.h>
#  include <rt/color.h>

#  define RT_BACKEND_PROVIDERS_MAX 10

// Note: when adding functions to this struct, don't forget to
// update the `rt_devreload_backend_setup` function and all
// the providers.
typedef struct s_rt_backend
{
	t_rt		*rt;
	const char	*name;

	size_t		width;
	size_t		height;
	uint8_t		pixel_size;

	int			(*init)(struct s_rt_backend *self);
	void		(*destroy)(struct s_rt_backend *self);
	void		(*update)(struct s_rt_backend *self);
	t_color		*(*render)(struct s_rt_backend *self);

	void		*data;
	t_obj		*objects;
}	t_rt_backend;

typedef struct s_rt_backend_provider
{
	const char		*name;
	t_rt_backend	*(*fn)(t_rt *rt, const char *name,
			size_t width, size_t height);
}	t_rt_backend_provider;

t_rt_backend_provider	*rt_backend_providers(void);
void					rt_backend_provider_register(
							t_rt_backend_provider provider);
t_rt_backend_provider	*rt_backend_provider_find(const char *name);

void					rt_backend_reload(t_rt *rt);
void					rt_backend_switch(t_rt *rt, const char *name);

# endif // __RT_RENDER_BACKEND_H__
#endif // BACKEND_H
