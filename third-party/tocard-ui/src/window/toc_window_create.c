/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_window_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:49:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 16:55:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/defaults.h>
#define __TOCARD_WINDOW_INTERNALS__
#include <tocard/window.h>
#include <stdlib.h>

static inline void	toc_window_construct(t_toc_window *window,
					t_toc_engine *engine, size_t width, size_t height)
{
	size_t			i;

	window->width = width;
	window->height = height;
	window->engine = engine;
	window->screen.def = (t_toc_screen_def){0};
	window->active = true;
	window->initialized = false;
	window->focused = true;
	window->hovered = false;
	window->mouse_pos = toc_vec2i(0, 0);
	i = 0;
	while (i < sizeof(window->keymap))
		window->keymap[i++] = false;
	toc_window_set_screen(window, toc_default_screen(), NULL);
}

t_toc_window	*toc_window_create(t_toc_engine *engine, const char *name,
					size_t width, size_t height)
{
	t_toc_window	*window;
	t_toc_list		*node;

	if (!engine || !name || !width || !height)
		return (NULL);
	window = malloc(sizeof(t_toc_window));
	if (!window)
		return (NULL);
	node = toc_list_create(window);
	if (!node)
		free(window);
	if (!node)
		return (NULL);
	window->handle = mlx_new_window(engine->mlx, width, height, name);
	if (!window->handle)
	{
		toc_list_clear(&node, &free);
		return (NULL);
	}
	window->name = name;
	toc_window_construct(window, engine, width, height);
	toc_list_push(&engine->windows, node);
	return (window);
}
