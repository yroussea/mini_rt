/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_handoff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:11:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 22:11:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

void	rt_backend_handoff(t_rt_backend *from, t_rt_backend *to)
{
	to->objects = from->objects;
	to->main_camera = from->main_camera;
}
