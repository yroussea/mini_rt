/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ray_generator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 16:43:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <math.h>

//a normre + ajouter camera dependent var + renomer fonction
void	eye_rays(t_ray *ray, float u, float v/*, t_camera (rotation et pos)*/)
{
	ray->direction = /* get_rotation */(t_vec3d){u, v, 1};
	ray->point = v3d_add(ray->center, ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 0};
}

float	get_width(t_rt_backend *backend, float x, float fov)
{
	return (-atan(fov / 2.) + (2 * atan(fov / 2.)) * (x) / backend->width);
}

float	get_height(t_rt_backend *backend, float y)
{
	return (-1 + 2 * (backend->height - 1 - y) / backend->height);
}
