/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:44:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 23:35:32 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRONTEND_H
# define FRONTEND_H
# undef FRONTEND_H
# ifndef __RT_RENDER_FRONTEND_H__
#  define __RT_RENDER_FRONTEND_H__

#  include <rt/app.h>

#  define RT_FRONTEND_PROVIDERS_MAX	16
#  define FRONTEND_SUPPORT_UI		0x1
#  define FRONTEND_SUPPORT_KEYBOARD	0x2
#  define FRONTEND_SUPPORT_MOUSE	0x4
#  define FRONTEND_SUPPORT_RESIZE	0x8

// Note: when adding functions to this struct, don't forget to
// update the `rt_devreload_frontend_setup` function and all
// the providers.
typedef struct s_rt_frontend
{
	const char	*name;
	int			flags;
	t_rt		*rt;

	size_t		width;
	size_t		height;
	size_t		scale;

	int			(*init)(struct s_rt_frontend *self);
	void		(*handoff)(struct s_rt_frontend *self);
	void		(*stop)(struct s_rt_frontend *self);
	void		(*destroy)(struct s_rt_frontend *self);

	void		*data;
}	t_rt_frontend;

typedef struct s_rt_frontend_provider
{
	const char		*name;
	t_rt_frontend	*(*fn)(t_rt *rt, const char *name,
			size_t width, size_t height);
}	t_rt_frontend_provider;

t_rt_frontend_provider	*rt_frontend_providers(void);
void					rt_frontend_provider_register(
							t_rt_frontend_provider provider);
t_rt_frontend_provider	*rt_frontend_provider_find(const char *name);

void					rt_frontend_reload(t_rt *rt);
void					rt_frontend_switch(t_rt *rt, const char *name);

# endif // __RT_RENDER_FRONTEND_H__
#endif // FRONTEND_H
