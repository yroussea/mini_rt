/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 18:58:49 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend/raytracer.h>

static void	*ft_memsets(void *s, uint64_t c, size_t n, uint8_t size)
{
	uint8_t	*ptr;
	uint8_t	value[4];

	if (s)
	{
		value[3] = (c >> 24) & 0xFF;
		value[2] = (c >> 16) & 0xFF;
		value[1] = (c >> 8) & 0xFF;
		value[0] = c & 0xFF;
		ptr = (uint8_t *)s;
		n *= size;
		while (n--)
			*ptr++ = value[n % size];
	}
	return (s);
}

int	rt_backend_raytracer_init(t_rt_backend *self)
{
	t_rt_backend_raytracer	*data;

	data = ft_calloc(1, sizeof(t_rt_backend_raytracer));
	if (!data)
		return (1);
	self->data = data;
	data->buffer = ft_calloc(self->width * self->height, sizeof(t_color));
	if (!data->buffer)
		return (1);
	// ft_memset(data->buffer, 255, self->width * self->height * sizeof(t_color));
	ft_memsets(data->buffer, 0xFFFFFFFF, self->width * self->height, sizeof(t_color));
	return (0);
}
