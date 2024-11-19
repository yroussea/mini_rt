/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_draw_blit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:58:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 18:22:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <tocard/draw.h>

void	toc_draw_blit(t_toc_screen *screen, t_toc_vec2i screen_pos,
			t_toc_texture *texture, double alpha)
{
	t_toc_vec2i		pos;
	t_toc_color		color;

	pos.y = 0;
	while (pos.y < texture->size.y)
	{
		pos.x = 0;
		while (pos.x < texture->size.x)
		{
			color = texture->data[pos.y * texture->size.x + pos.x];
			color.a = alpha;
			toc_draw_pixel(screen, toc_vec2i_add(screen_pos, pos), color);
			pos.x++;
		}
		pos.y++;
	}
}
