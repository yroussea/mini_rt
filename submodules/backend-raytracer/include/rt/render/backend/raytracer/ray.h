/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:51:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 07:11:29 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
#include "ft/math/matrix.h"
#include "rt/objects.h"
# undef RAY_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_RAY_H__

#  include <rt/render/backend.h>
#  include <ft/math/vector.h>
#  include <rt/color.h>

typedef struct s_ray
{
	t_vec3d				point;
	t_vec3d				center;
	t_vec3d				direction;
	t_vec3d				inv_direction;
	t_vec3d				hit_point;
	t_color				color;
}	t_ray
__attribute__((aligned(32)));

void	rt_backend_raytracer_init_ray(t_ray *ray,
		t_vec3d coo, const t_mat3d *rot);
t_vec3d	rt_backend_raytracer_get_rays_relative_coo(
	t_rt_backend *backend, double x, double y, double fov);

# endif // __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#endif // RAY_H
