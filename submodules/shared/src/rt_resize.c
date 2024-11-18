/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_resize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:12:16 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:33:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <rt/log.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>

void	rt_resize(t_rt *rt, size_t width, size_t height)
{
	if (rt->frontend && !(rt->frontend->flags & FRONTEND_SUPPORT_RESIZE))
	{
		rt_warn(rt, "frontend does not support resizing\n");
		return ;
	}
	rt_trace(rt, "resizing from %d*%d to %d*%d\n",
		(int)rt->width, (int)rt->height, (int)width, (int)height);
	rt->width = ft_max(width, 300);
	rt->height = ft_max(height, 180);
	rt_frontend_reload(rt);
	rt_backend_reload(rt);
}
