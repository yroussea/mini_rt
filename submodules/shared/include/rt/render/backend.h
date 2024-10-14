/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:57:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 21:20:21 by kiroussa         ###   ########.fr       */
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

typedef struct s_rt_backend
{
	t_rt		*rt;
	const char	*name;

	size_t		width;
	size_t		height;

	int			(*init)(struct s_rt_backend *self);
	void		(*destroy)(struct s_rt_backend *self);
	void		(*update)(struct s_rt_backend *self);
	t_color		*(*render)(struct s_rt_backend *self);

	void		*data;
}	t_rt_backend;

typedef struct s_rt_backend_provider
{
	const char		*name;
	t_rt_backend	*(*fn)(t_rt *rt, const char *name,
			size_t width, size_t height);
}	t_rt_backend_provider;

t_rt_backend_provider	*rt_backend_providers(void);
t_rt_backend_provider	*rt_backend_provider_find(const char *name);

void					rt_backend_provider_register(
							t_rt_backend_provider provider);

# endif // __RT_RENDER_BACKEND_H__
#endif // BACKEND_H
