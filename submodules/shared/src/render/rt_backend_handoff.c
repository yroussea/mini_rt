/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_handoff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:11:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 23:12:16 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>
# include <stdio.h>

void	rt_backend_handoff(t_rt_backend *from, t_rt_backend *to)
{
	printf("handoff target = %p, from = %p\n", to, from);
	to->objects = from->objects;
	printf("objects set to %p\n", to->objects);
	to->main_camera = from->main_camera;
	printf("main_camera set to %p\n", to->main_camera);
}
