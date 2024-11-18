/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_move_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:47:10 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 01:01:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include "rt/objects.h"
#include <rt/render/backend.h>

void	rt_move_camera(t_rt *rt, t_vec3d vector_move)
{
	t_camera	*camera;

	camera = rt->backend->main_camera;
	camera->point = v3d_add(&camera->point, &vector_move);
	rt_backend_reload(rt);
}

void	rt_rotate_camera(t_rt *rt, double phi_rotate, double theta_rotate)
{
	t_camera	*camera;

	camera = rt->backend->main_camera;
	camera->phi += phi_rotate;
	camera->theta += theta_rotate;
	rt_backend_reload(rt);
}
