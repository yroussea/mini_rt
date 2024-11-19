/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_engine_await.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:23:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/14 08:34:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL2/SDL_scancode.h>
#define __TOCARD_WINDOW_INTERNALS__
#include <tocard/window.h>

static int	toc_update_windows(t_toc_engine *engine)
{
	t_toc_list			*node;
	t_toc_window		*win;
	size_t				active;

	node = engine->windows;
	active = 0;
	while (node)
	{
		win = (t_toc_window *) node->data;
		if (!win->initialized)
			toc_window_init(win);
		if (win->active)
			toc_window_update(win);
		active += win->active;
		node = node->next;
	}
	return (active);
}

static int	toc_mlx_hook(void *param)
{
	t_toc_engine	*engine;
	size_t			active;

	engine = (t_toc_engine *) param;
	if (engine && engine->mlx && !engine->windows)
		mlx_loop_end(engine->mlx);
	if (!engine || !engine->windows)
		return (0);
	if (engine->_hook_pre)
		engine->_hook_pre(engine);
	active = toc_update_windows(engine);
	if (engine->_hook_post)
		engine->_hook_post(engine);
	if (active == 0)
		mlx_loop_end(engine->mlx);
	return (0);
}

static void	toc_engine_cleanup_windows(t_toc_engine *engine)
{
	t_toc_list		*node;

	node = engine->windows;
	while (node)
	{
		toc_window_close((t_toc_window *) node->data);
		node = node->next;
	}
	toc_list_clear(&engine->windows, &free);
}

void	toc_engine_await(t_toc_engine *engine)
{
	t_toc_window	*win;
	t_toc_list		*node;

	if (!engine->windows)
		return ;
	node = engine->windows;
	while (node)
	{
		win = (t_toc_window *) node->data;
		if (!win->initialized)
			toc_window_init(win);
		node = node->next;
	}
	mlx_loop_hook(engine->mlx, toc_mlx_hook, engine);
	mlx_set_fps_goal(engine->mlx, 120);
	mlx_loop(engine->mlx);
	toc_engine_cleanup_windows(engine);
}
