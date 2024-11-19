/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:02:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/12 19:29:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/draw.h>

static void	toc_plot_low(
	t_toc_screen *screen,
	t_toc_vec2i v1,
	t_toc_vec2i v2,
	t_toc_color color
) {
	t_toc_vec2i	diff;
	t_toc_vec2i	pos;
	int			yi;
	int			d;

	diff = toc_vec2i(v2.x - v1.x, v2.y - v1.y);
	yi = 1;
	if (diff.y < 0)
		yi = -1;
	if (diff.y < 0)
		diff.y = -diff.y;
	d = (2 * diff.y) - diff.x;
	pos = toc_vec2i(v1.x, v1.y);
	while (pos.x < v2.x)
	{
		toc_draw_pixel(screen, pos, color);
		if (d > 0)
			pos.y += yi;
		if (d > 0)
			d += (2 * (diff.y - diff.x));
		else
			d += 2 * diff.y;
		pos.x++;
	}
}

static void	toc_plot_high(
	t_toc_screen *screen,
	t_toc_vec2i v1,
	t_toc_vec2i v2,
	t_toc_color color
) {
	t_toc_vec2i	diff;
	t_toc_vec2i	pos;
	int			xi;
	int			d;

	diff = toc_vec2i(v2.x - v1.x, v2.y - v1.y);
	xi = 1;
	if (diff.x < 0)
		xi = -1;
	if (diff.x < 0)
		diff.x = -diff.x;
	d = diff.x + diff.x - diff.y;
	pos = toc_vec2i(v1.x, v1.y);
	while (pos.y < v2.y)
	{
		toc_draw_pixel(screen, pos, color);
		if (d > 0)
			pos.x += xi;
		if (d > 0)
			d += (diff.x - diff.y) + (diff.x - diff.y);
		else
			d += diff.x + diff.x;
		pos.y++;
	}
}

static int	toc_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * @note Credit: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void	toc_draw_line(
	t_toc_screen *screen,
	t_toc_vec2i v1,
	t_toc_vec2i v2,
	t_toc_color	color
) {
	if (toc_abs(v2.y - v1.y) < toc_abs(v2.x - v1.x))
	{
		if (v1.x > v2.x)
			toc_plot_low(screen, v2, v1, color);
		else
			toc_plot_low(screen, v1, v2, color);
	}
	else
	{
		if (v1.y > v2.y)
			toc_plot_high(screen, v2, v1, color);
		else
			toc_plot_high(screen, v1, v2, color);
	}
}
