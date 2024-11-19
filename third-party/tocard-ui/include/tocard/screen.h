/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:47:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:06:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREEN_H
# define SCREEN_H
# undef SCREEN_H
# ifndef __TOCARD_SCREEN_H__
#  define __TOCARD_SCREEN_H__

#  include <tocard/element.h>
#  include <tocard/util.h>
#  include <stdbool.h>
#  include <stddef.h>

typedef struct s_toc_window		t_toc_window;
typedef struct s_toc_screen		t_toc_screen;

typedef void					t_toc_screen_generic_fn(t_toc_screen *screen);
typedef bool					t_toc_screen_render_fn(t_toc_screen *screen,
										t_toc_vec2i mouse_pos);
typedef bool					t_toc_screen_key_fn(t_toc_screen *screen,
										int key, int state, int last_state);
typedef bool					t_toc_screen_mouse_fn(t_toc_screen *screen,
									t_toc_vec2i mouse_pos, int button,
									int action);
typedef void					t_toc_screen_elem_act(t_toc_screen *screen,
										t_toc_elem *element);

/**
 * @brief A screen definition structure, commonly used as a class.
 */
typedef struct s_toc_screen_def
{
	const char				*id;

	t_toc_screen_generic_fn	*init;
	t_toc_screen_render_fn	*render;
	t_toc_screen_key_fn		*key;
	t_toc_screen_mouse_fn	*mouse;
	t_toc_screen_elem_act	*action;
	t_toc_screen_generic_fn	*close;
	t_toc_screen_generic_fn	*destroy;
}	t_toc_screen_def;

/**
 * @brief A screen instance as a structure.
 */
typedef struct s_toc_screen
{
	t_toc_list			*elements;

	size_t				width;
	size_t				height;

	t_toc_window		*window;
	t_toc_screen_def	def;

	void				*image;

	void				*data;
}	t_toc_screen;

void	toc_screen_create(t_toc_screen *screen, t_toc_window *window,
			t_toc_screen_def def, void *data);
void	toc_screen_destroy(t_toc_screen *screen);

void	toc_screen_resize(t_toc_screen *screen, size_t width, size_t height);

void	toc_screen_add(t_toc_screen *screen, t_toc_elem *elem);

# endif // __TOCARD_SCREEN_H__
#endif // SCREEN_H
