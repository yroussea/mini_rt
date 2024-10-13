/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backend.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:57:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 01:00:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BACKEND_H
# define BACKEND_H
# undef BACKEND_H
# ifndef __RT_RENDER_BACKEND_H__
#  define __RT_RENDER_BACKEND_H__

#  include <rt/app.h>

#  define RT_BACKEND_PROVIDERS_MAX 10

typedef struct s_rt_render_backend
{
	const char		*name;
	int				(*init)(t_rt *rt);
	void			(*destroy)(t_rt *rt);
	void			(*render)(t_rt *rt);
}	t_rt_render_backend;

typedef struct s_rt_backend_provider
{
	const char				*name;
	t_rt_render_backend		*(*fn)(t_rt *rt);
}	t_rt_backend_provider;

extern t_rt_backend_provider	g_backend_providers[RT_BACKEND_PROVIDERS_MAX];

# endif // __RT_RENDER_BACKEND_H__
#endif // BACKEND_H
