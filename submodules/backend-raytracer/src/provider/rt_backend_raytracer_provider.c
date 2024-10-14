/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_provider.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:23:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 21:33:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend/raytracer.h>

t_rt_backend	*rt_backend_raytracer_provider(t_rt *rt, const char *name,
					size_t width, size_t height)
{
	static t_rt_backend	backend;

	ft_memset(&backend, 0, sizeof(t_rt_backend));
	backend.rt = rt;
	backend.name = name;
	backend.width = width;
	backend.height = height;
	backend.init = rt_backend_raytracer_init;
	backend.destroy = rt_backend_raytracer_destroy;
	backend.render = rt_backend_raytracer_render;
	backend.update = NULL;
	return (&backend);
}
