/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_draw_rect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:11:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/12 19:28:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/draw.h>

static void	toc_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	toc_draw_rect(t_toc_screen *screen, t_toc_vec2i p1, t_toc_vec2i p2,
			t_toc_color color)
{
	t_toc_vec2i	pos;

	if (p1.x > p2.x)
		toc_swap(&p1.x, &p2.x);
	if (p1.y > p2.y)
		toc_swap(&p1.y, &p2.y);
	pos.y = p1.y;
	while (pos.y < p2.y)
	{
		pos.x = p1.x;
		while (pos.x < p2.x)
		{
			toc_draw_pixel(screen, pos, color);
			pos.x++;
		}
		pos.y++;
	}
}
