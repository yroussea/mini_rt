/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 02:12:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/color.h>
#include <rt/render/backend.h>

#define BRIGHT_PURPLE 0xFFab4cef
#define DARK_RED 0xFFF44336
#define SYS_write 0x1

# include <unistd.h>

ssize_t	ft_write(int fd, const char *buf, size_t count);

int	ptdr(void)
{
	return (1);
}

int	rt_backend_dummy_init(t_rt_backend *self)
{
	return (ptdr());

	static const t_color	dummy_default = {.rgba = DARK_RED};
	t_color					*buffer;
	size_t					x;
	size_t					y;

	// ft_write(STDOUT_FILENO, "BORDEL\n", 7);
	// buffer = ft_calloc(self->width * self->height, sizeof(t_color));
	// if (!buffer)
	// 	return (1);
	// ((char *)0)[0] = 0;
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
