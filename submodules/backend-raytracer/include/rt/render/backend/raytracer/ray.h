/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:51:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/25 00:55:38 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# undef RAY_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_RAY_H__

#  include <rt/render/backend.h>
#  include <ft/math/vector.h>
#  include <rt/color.h>

typedef struct s_ray
{
	t_vec3d	point;
	t_vec3d	center;
	t_vec3d	direction;
	t_vec3d	hit_point;
	t_color	color;
}	t_ray;

void	eye_rays(t_ray *ray, float u, float v, float fov);
float	get_width(t_rt_backend *backend, float x);
float	get_height(t_rt_backend *backend, float y);

# endif // __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#endif // RAY_H
