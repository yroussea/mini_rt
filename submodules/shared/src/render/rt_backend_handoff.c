/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_handoff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:11:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 00:36:58 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

void	rt_backend_handoff(t_rt_backend *from, t_rt_backend *to)
{
	to->width = from->width;
	to->height = from->height;
	to->objects = from->objects;
	to->main_camera = from->main_camera;
}
