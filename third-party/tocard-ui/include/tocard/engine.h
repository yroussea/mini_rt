/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:44:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 08:11:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H
# undef ENGINE_H
# ifndef __TOCARD_ENGINE_H__
#  define __TOCARD_ENGINE_H__

#  include <tocard/util.h>
#  include <mlx.h>

typedef struct s_toc_engine	t_toc_engine;

typedef void				t_toc_engine_hook(t_toc_engine *engine);

/**
 * @brief A engine instance as a structure.
 *
 * TODO: fonts, assets?.
 */
typedef struct s_toc_engine
{
	t_toc_engine_hook	*_hook_pre;
	t_toc_engine_hook	*_hook_post;

	void				*mlx;
	t_toc_list			*windows;
	t_toc_list			*fonts;
}	t_toc_engine;

t_toc_engine	*toc_engine_create(void);
void			toc_engine_destroy(t_toc_engine *engine);

void			toc_engine_await(t_toc_engine *engine);
void			toc_engine_exit(t_toc_engine *engine);

void			toc_engine_hook_pre(t_toc_engine *engine,
					t_toc_engine_hook *hook);
void			toc_engine_hook_post(t_toc_engine *engine,
					t_toc_engine_hook *hook);

# endif // __TOCARD_ENGINE_H__
#endif // ENGINE_H
