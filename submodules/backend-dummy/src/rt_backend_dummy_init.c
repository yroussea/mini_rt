/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:22:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/color.h>
#include <rt/render/backend.h>

int	rt_backend_dummy_init(t_rt_backend *self)
{
	static const t_color	dummy_default = {.rgba = 0xFFab4cef};
	t_color					*buffer;
	size_t					x;
	size_t					y;

	buffer = ft_calloc(self->width * self->height, sizeof(t_color));
	if (!buffer)
		return (1);
	y = 0;
	while (y < self->height)
	{
		x = 0;
		while (x < self->width)
		{
			buffer[y * self->width + x].rgba = dummy_default.rgba;
			x++;
		}
		y++;
	}
	self->data = buffer;
	return (0);
}
