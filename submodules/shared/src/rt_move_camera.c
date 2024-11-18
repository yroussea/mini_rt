/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_move_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:47:10 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:14:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/matrix.h"
#include "ft/math/vector.h"
#include "rt/objects.h"
#include <rt/render/backend.h>

void	rt_move_camera(t_rt *rt, t_vec3d vector_move)
{
	t_camera	*camera;
	t_mat3d		rotation;
	t_vec3d		move;

	camera = rt->backend->main_camera;
	rotation = m3d_rot(camera->theta, camera->phi, 0);
	move = v3d_mult_m3d(vector_move, rotation);
	camera->point = v3d_add(&camera->point, &move);
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
