/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:50:24 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/17 23:48:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <termengine.h>

void	te_img_init(t_te_img *img, uint32_t row, uint32_t col, uint32_t *data)
{
	if (!img)
		return ;
	img->row = row;
	img->col = col;
	img->x = 0;
	img->y = 0;
	img->data = data;
}

void	te_img_destroy(t_te_img *img)
{
	if (img)
	{
		img->col = 0;
		img->row = 0;
		free(img->data);
	}
}

void	te_img_set_pixel(t_te_img *img, t_vec2 pos, uint32_t color)
{
	const uint32_t	index = (img->row * pos.y) + pos.x;

	img->data[index] = color;
}
