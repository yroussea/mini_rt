/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:54:44 by kiroussa          #+#    #+#             */
/*   Updated: 2024/06/10 16:59:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# undef DRAW_H
# ifndef __TOCARD_DRAW_H__
#  define __TOCARD_DRAW_H__

#  include <tocard/texture.h>
#  include <tocard/window.h>
#  include <tocard/util.h>

void	toc_draw_blit(t_toc_screen *screen, t_toc_vec2i coords,
			t_toc_texture *texture, double alpha);

void	toc_draw_line(t_toc_screen *screen, t_toc_vec2i start, t_toc_vec2i end,
			t_toc_color color);

void	toc_draw_pixel(t_toc_screen *screen, t_toc_vec2i coords,
			t_toc_color color);

void	toc_draw_rect(t_toc_screen *screen, t_toc_vec2i start, t_toc_vec2i end,
			t_toc_color color);

#  define TEXT_ALIGN_LEFT 0x00000001
#  define TEXT_ALIGN_CENTER 0x00000002
#  define TEXT_ALIGN_RIGHT 0x00000003
#  define TEXT_NO_WRAP 0x00000004

typedef struct s_text_data
{
	const char	*text;
	int			flags;
	t_toc_color	color;
}	t_text_data;

void	toc_draw_text(t_toc_screen *screen, t_toc_vec2i coords,
			t_toc_vec2i max_size, t_text_data data);

# endif // __TOCARD_DRAW_H__
#endif // DRAW_H
