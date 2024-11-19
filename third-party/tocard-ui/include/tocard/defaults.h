/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:22:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:28:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file defaults.h
 * @brief Default values for themes, colors, spacings, etc.
 */

#ifndef DEFAULTS_H
# define DEFAULTS_H
# undef DEFAULTS_H
# ifndef __TOCARD_DEFAULTS_H__
#  define __TOCARD_DEFAULTS_H__

#  include <tocard/texture.h>
#  include <tocard/window.h>

#  ifndef TOCARD_DEFAULT_BG
#   define TOCARD_DEFAULT_BG 0xFF11111b
#  endif // TOCARD_DEFAULT_BG

#  ifndef TOCARD_DEFAULT_BG_UNFOCUSED
#   define TOCARD_DEFAULT_BG_UNFOCUSED 0xFF1e1e2e
#  endif // TOCARD_DEFAULT_BG_UNFOCUSED

/* Default screens */

#  ifndef TOCARD_DEFAULT_SCREEN_ID
#   define TOCARD_DEFAULT_SCREEN_ID "toc:default"
#  endif // TOCARD_DEFAULT_SCREEN_ID

t_toc_screen_def	toc_default_screen(void);

#  ifndef TOCARD_ABOUT_SCREEN_ID
#   define TOCARD_ABOUT_SCREEN_ID "toc:about"
#  endif // TOCARD_ABOUT_SCREEN_ID
//
t_toc_screen_def	toc_default_screen_about(void);

/* Default elements */

typedef struct s_toc_button_data
{
	const char		*text;
	double			hover;
	double			clicked;
	t_toc_texture	*icon;
	t_toc_texture	*texture;
	t_toc_texture	*texture_hover;
	t_toc_texture	*texture_clicked;
}	t_toc_button_data;

t_toc_elem			*toc_button(int id, t_toc_vec2i pos, t_toc_vec2i size,
						const char *text);

typedef struct s_toc_checkbox_data
{
	const char	*text;
	bool		*value;
}	t_toc_checkbox_data;

t_toc_elem			*toc_checkbox(int id, t_toc_vec2i pos, t_toc_vec2i size,
						t_toc_checkbox_data *data);

# endif // __TOCARD_DEFAULTS_H__
#endif // DEFAULT_H
