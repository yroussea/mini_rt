/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:50:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:07:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H
# undef ELEMENT_H
# ifndef __TOCARD_ELEMENT_H__
#  define __TOCARD_ELEMENT_H__

#  include <tocard/window.h>
#  include <tocard/util.h>
#  include <stdbool.h>
#  include <stdlib.h>

typedef struct s_toc_elem		t_toc_elem;
typedef struct s_toc_screen		t_toc_screen;

typedef void					t_toc_elem_generic_fn(t_toc_elem *elem);
typedef void					t_toc_elem_render_fn(t_toc_elem *elem,
									t_toc_vec2i mouse_pos);
typedef void					t_toc_elem_key_fn(t_toc_elem *elem, int key,
									int state, int last_state);
typedef void					t_toc_elem_mouse_fn(t_toc_elem *elem,
									t_toc_vec2i mouse_pos, int button,
									int action);

typedef struct s_toc_elem_def
{
	t_toc_elem_generic_fn	*init;
	t_toc_elem_render_fn	*render;
	t_toc_elem_key_fn		*key;
	t_toc_elem_mouse_fn		*mouse;
	t_toc_elem_generic_fn	*destroy;
}	t_toc_elem_def;

typedef struct s_toc_elem
{
	t_toc_screen	*screen;
	t_toc_elem_def	def;
	int				id;

	int				x;
	int				y;
	size_t			width;
	size_t			height;

	bool			last_click;
	void			*data;

	bool			enabled;
	bool			visible;
	bool			focused;
}	t_toc_elem;

t_toc_elem	*toc_elem_create(int id, t_toc_elem_def definition);
void		toc_elem_destroy(t_toc_elem *elem);

bool		toc_elem_is_hovered(t_toc_elem *elem, t_toc_vec2i mouse_pos);

# endif // __TOCARD_ELEMENT_H__
#endif // ELEMENT_H
