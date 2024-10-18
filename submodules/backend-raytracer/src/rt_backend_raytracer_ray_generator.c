/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ray_generator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/18 19:27:00 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <math.h>

//a normre + ajouter camera dependent var + renomer fonction
static float	get_oposite(char fov)
{
	float x = atan(fov / 2.);
	return (x);
}

void	eye_rays(t_ray *ray, float u, float v/*, t_camera (rotation et pos)*/)
{
	ray->direction = /* get_rotation */(t_vec3d){u, v, 1};
	ray->point = ft_vec3d_add(ray->center, ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 0};
}

float	get_width(t_rt_backend *backend, float x, char fov)
{
	return (-get_oposite(fov) + (2 * get_oposite(fov)) * (x) / backend->width);
}

float	get_height(t_rt_backend *backend, float y)
{
	return (-1 + 2 * (backend->width - 1 - y) / backend->height);
}
