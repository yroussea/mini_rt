/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:12:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 18:56:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H
# undef WINDOW_H
# ifndef __TOCARD_WINDOW_H__
#  define __TOCARD_WINDOW_H__

#  include <tocard/engine.h>
#  include <tocard/screen.h>
#  include <stddef.h>
#  include <stdbool.h>

/**
 * @brief A window instance as a structure.
 */
typedef struct s_toc_window
{
	void			*handle;
	t_toc_engine	*engine;

	const char		*name;
	size_t			width;
	size_t			height;
	bool			initialized;

	t_toc_screen	screen;
	bool			active;

	t_toc_vec2i		mouse_pos;
	bool			keymap[8192];

	bool			focused;
	bool			hovered;
}	t_toc_window;

/**
 * @brief Create a new window.
 *
 * @param engine The engine instance.
 * @param name The name of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 *
 * @return The window instance.
 */
t_toc_window	*toc_window_create(t_toc_engine *engine, const char *name,
					size_t width, size_t height);

/**
 * @brief Close the window.
 *
 * @param window The window to close.
 */
void			toc_window_close(t_toc_window *window);

/**
 * @brief Set the screen of the window.
 *
 * @param window The window to set the screen.
 * @param screen_def The screen definition to set.
 * @param data The data to pass to the screen.
 */
void			toc_window_set_screen(t_toc_window *window,
					t_toc_screen_def screen_def, void *data);

#  ifdef __TOCARD_WINDOW_INTERNALS__

/**
 * @brief Initializes the window and its hooks.
 *
 * @param window The window to initialize.
 */
void			toc_window_init(t_toc_window *window);

/**
 * @brief Update the window.
 *
 * @param window The window to update.
 */
void			toc_window_update(t_toc_window *window);

// /* MLX Event Hooks */ //

int				toc_window_event(int event, void *param);
int				toc_window_keydown(int event, void *param);
int				toc_window_keyup(int event, void *param);
int				toc_window_mousedown(int event, void *param);
int				toc_window_mouseup(int event, void *param);
int				toc_window_mousewheel(int event, void *param);

#  endif // __TOCARD_WINDOW_INTERNALS__

# endif // __TOCARD_WINDOW_H__
#endif // WINDOW_H
