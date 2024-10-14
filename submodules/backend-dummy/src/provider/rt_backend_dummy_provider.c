/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_provider.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:23:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 07:16:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend.h>

int		rt_backend_dummy_init(t_rt_backend *self);
void	rt_backend_dummy_destroy(t_rt_backend *self);
t_color	*rt_backend_dummy_render(t_rt_backend *self);

t_rt_backend	*rt_backend_dummy_provider(t_rt *rt, size_t width,
					size_t height)
{
	static t_rt_backend	backend;

	ft_memset(&backend, 0, sizeof(t_rt_backend));
	backend.rt = rt;
	backend.name = "dummy";
	backend.width = width;
	backend.height = height;
	backend.init = rt_backend_dummy_init;
	backend.destroy = rt_backend_dummy_destroy;
	backend.render = rt_backend_dummy_render;
	backend.update = NULL;
	return (&backend);
}
