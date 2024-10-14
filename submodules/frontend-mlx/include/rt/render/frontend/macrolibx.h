/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macrolibx.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:08:56 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 21:36:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROLIBX_H
# define MACROLIBX_H
# undef MACROLIBX_H
# ifndef __RT_RENDER_FRONTEND_MACROLIBX_H__
#  define __RT_RENDER_FRONTEND_MACROLIBX_H__

#  include <rt/render/frontend.h>
#  include <tocard/engine.h>
#  include <tocard/window.h>

typedef struct s_rt_frontend_mlx
{
	t_toc_engine	*engine;
	t_toc_window	*main_window;
}	t_rt_frontend_mlx;

int					rt_frontend_mlx_init(t_rt_frontend *self);
void				rt_frontend_mlx_destroy(t_rt_frontend *self);
void				rt_frontend_mlx_handoff(t_rt_frontend *self,
						t_rt_frontend *prev);

t_rt_frontend		*rt_frontend_mlx_provider(t_rt *rt, const char *name,
						size_t width, size_t height);

t_toc_screen_def	rt_screen_main(void);

# endif // __RT_RENDER_FRONTEND_MACROLIBX_H__
#endif // MACROLIBX_H
