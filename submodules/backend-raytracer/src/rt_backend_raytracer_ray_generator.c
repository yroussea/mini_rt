/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ray_generator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 14:35:57 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include <rt/render/backend/raytracer.h>
#include <math.h>

#include <stdio.h>
//a normre + ajouter camera dependent var + renomer fonction
//fov n est pas une var env, mais fais partie de la cam
#define RT_FLAT_VIEW_TYPE 0
#if RT_FLAT_VIEW_TYPE == 1

void	eye_rays(t_ray *ray, double u, double v, double fov/*, t_camera (rotation et pos)*/)
{
	const	double k = u * fov / 2;
	(void)k;
	ray->direction = /* get_rotation */(t_vec3d){sin(k), v, cos(k)};
	ray->point = v3d_add(&ray->center, &ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 255};
	ray->direction = v3d_norm(&ray->direction);
}

#else

void	eye_rays(t_ray *ray, double u, double v, double fov/*, t_camera (rotation et pos)*/)
{
	(void)fov;
	ray->direction = /* get_rotation */(t_vec3d){u, v, 1};
	ray->point = v3d_add(&ray->center, &ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 255};
	ray->direction = v3d_norm(&ray->direction);
}

#endif

double	get_width(t_rt_backend *backend, double x)
{
	const double	resolution = (float)backend->width / backend->height;

	return (-resolution + (2 * resolution * (x) / backend->width));
}

double	get_height(t_rt_backend *backend, double y)
{
	return (-1 + 2 * (backend->height - 1 - y) / backend->height);
}
