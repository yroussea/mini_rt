/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:06:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:55:58 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include <mlx_manage.h>
#include <stdlib.h>
#include <maths.h>

static int	vec_to_rgb(t_vec3d v)
{
	int		r;
	int		g;
	int		b;

	r = 255 * ft_fmin(ft_fmax(0, v.x), 1);
	g = 255 * ft_fmin(ft_fmax(0, v.y), 1);
	b = 255 * ft_fmin(ft_fmax(0, v.z), 1);
	return (0xFF000000 + (r << 16) + (g << 8) + b);
}

void	mm_draw_pixel(uint x, t_vec3d colors)
{
	static t_mdata	*mdata = NULL;
	uint			pixel;

	if (!mdata)
		mm_getmdata(&mdata);
	pixel = mdata->pixelisation;
	mdata->colors[x * pixel] = colors;
}

void	mm_draw_ligne(uint y)
{
	static t_mdata	*data = NULL;
	int				col;
	uint			x;
	uint			k;
	uint			j;

	if (!data)
		mm_getmdata(&data);
	x = 0;
	while (x < WIDTH)
	{
		j = 0;
		col = vec_to_rgb(data->colors[x]);
		while (j < data->pixelisation && x + j < WIDTH)
		{
			k = 0;
			while (k < data->pixelisation && k + y < HEIGHT)
				mlx_set_image_pixel(data->mlx, data->img, x + j, y + k++, col);
			j++;
		}
		x += data->pixelisation;
	}
}

void	mm_draw_image(t_mdata *mdata)
{
	mlx_put_image_to_window(mdata->mlx, mdata->wind, mdata->img, 0, 0);
}
