/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_resize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:25:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:37:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __TOCARD_WINDOW_INTERNALS__
#include <tocard/window.h>

static void	toc_image_copy(void *new_img, t_toc_screen *screen,
				size_t width, size_t height)
{
	const void	*mlx = screen->window->engine->mlx;
	size_t		x;
	size_t		y;
	int			color;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			color = mlx_get_image_pixel((void *) mlx, screen->image, x, y);
			mlx_set_image_pixel((void *) mlx, new_img, x, y, color);
			x++;
		}
		y++;
	}
}

void	toc_screen_resize(t_toc_screen *screen, size_t width, size_t height)
{
	const void	*mlx = screen->window->engine->mlx;
	void		*new_img;

	if (!screen || !width || !height)
		return ;
	if (width == screen->width && height == screen->height)
		return ;
	new_img = mlx_new_image((void *) mlx, width, height);
	if (!new_img)
		return ;
	if (screen->image)
	{
		toc_image_copy(new_img, screen,
			toc_min(width, screen->width), toc_min(height, screen->height));
		mlx_destroy_image((void *) mlx, screen->image);
	}
	screen->image = new_img;
	screen->width = width;
	screen->height = height;
	toc_window_update(screen->window);
}
