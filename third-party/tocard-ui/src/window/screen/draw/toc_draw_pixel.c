/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_draw_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:16:43 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/12 19:28:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/draw.h>

static inline t_toc_color	toc_color_blend(t_toc_color c1, t_toc_color c2)
{
	t_toc_color	result;
	float		alpha;

	alpha = (float)c1.a / 255.0;
	result.r = (1 - alpha) * c2.r + alpha * c1.r;
	result.g = (1 - alpha) * c2.g + alpha * c1.g;
	result.b = (1 - alpha) * c2.b + alpha * c1.b;
	result.a = 0xFF;
	return (result);
}

void	toc_draw_pixel(t_toc_screen *screen, t_toc_vec2i coords,
			t_toc_color color)
{
	int	prev_color;

	if (screen && screen->image && coords.x >= 0
		&& coords.x < (int) screen->width && coords.y >= 0
		&& coords.y < (int) screen->height)
	{
		if (color.value && color.a == 0xFF)
			mlx_set_image_pixel(screen->window->engine->mlx, screen->image,
				coords.x, coords.y, color.value);
		else if (color.value)
		{
			prev_color = mlx_get_image_pixel(screen->window->engine->mlx,
					screen->image, coords.x, coords.y);
			color = toc_color_blend(color, (t_toc_color){prev_color});
			mlx_set_image_pixel(screen->window->engine->mlx, screen->image,
				coords.x, coords.y, color.value);
		}
	}
}
