/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_bumpmap.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:50:01 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/16 00:51:53 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>

#define RT_SCALE_BUMPMAP 1
int	rt_backend_raytracer_bumpmap_coo(
	const float u,
	const float v,
	const t_vec2i size)
{ 
	return ((int)(v * RT_SCALE_BUMPMAP) % size.x + \
		 ((int)(u * RT_SCALE_BUMPMAP) % size.y) * size.x);
}

t_vec3d	rt_backend_raytracer_bumpmap(
	const t_vec3d *vec,
	const t_vec3d *bump_color,
	const int coo)
{
	static const t_vec3d	diff = (t_vec3d){-1, -1, -1};
	const t_vec3d			rgb = bump_color[coo];
	const t_vec3d			bump = v3d_addmult(&diff, &rgb, 2);

	return (v3d_mult_v3d(vec, &bump));
}

