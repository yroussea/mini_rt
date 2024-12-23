/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_provider.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:02:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 18:26:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/frontend/macrolibx.h>

t_rt_frontend	*rt_frontend_mlx_provider(t_rt *rt, const char *name,
					size_t width, size_t height)
{
	static t_rt_frontend	frontend = {0};

	ft_memset(&frontend, 0, sizeof(t_rt_frontend));
	frontend.rt = rt;
	frontend.name = name;
	frontend.width = width;
	frontend.height = height;
	frontend.init = rt_frontend_mlx_init;
	frontend.handoff = rt_frontend_mlx_handoff;
	frontend.stop = rt_frontend_mlx_stop;
	frontend.destroy = rt_frontend_mlx_destroy;
	return (&frontend);
}
