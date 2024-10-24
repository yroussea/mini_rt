/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ray_generator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/25 01:23:48 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include <rt/render/backend/raytracer.h>
#include <math.h>

#include <stdio.h>
//a normre + ajouter camera dependent var + renomer fonction
void	eye_rays(t_ray *ray, float u, float v, float fov/*, t_camera (rotation et pos)*/)
{
	const	float k = u * fov / 2;
	(void)k;
	ray->direction = /* get_rotation */(t_vec3d){sin(k), v, cos(k)};
	ray->point = v3d_add(ray->center, ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 0};
	// printf("%f %f %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
	ray->direction = v3d_norm(ray->direction);
	// printf("\t%f %f %f\n", ray->direction.x, ray->direction.y, ray->direction.z);
}

float	get_width(t_rt_backend *backend, float x)
{
	return (-1 + (2 * 1 * (x) / backend->width));
}

float	get_height(t_rt_backend *backend, float y)
{
	return (-1 + 2 * (backend->height - 1 - y) / backend->height);
}
