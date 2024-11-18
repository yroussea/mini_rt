/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ray_generator.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:14:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:14:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <rt/render/backend/raytracer/option.h>

void	rt_backend_raytracer_init_ray(
	t_ray *ray, t_vec3d coo, const t_mat3d *rot
)
{
	ray->direction = v3d_mult_m3d(coo, *rot);
	ray->point = v3d_add(&ray->center, &ray->direction);
	ray->color = (t_color){.r = 0, .g = 0, .b = 0, .a = 255};
	ray->direction = v3d_norm(&ray->direction);
	ray->inv_direction = v3d_inv(&ray->direction);
}

#if RT_NO_FISH_EYE

t_vec3d	rt_backend_raytracer_get_rays_relative_coo(
	t_rt_backend *backend, double x, double y, double fov
)
{
	const double	res = (float)backend->width / backend->height;
	const double	u = -res + (2 * res * (x) / backend->width);
	const double	v = -1 + 2 * (backend->height - 1 - y) / backend->height;

	(void)fov;
	return (v3d(u, v, 1));
}

#else

t_vec3d	rt_backend_raytracer_get_rays_relative_coo(
	t_rt_backend *backend, double x, double y, double fov
)
{
	const double	res = (float)backend->width / backend->height;
	const double	u = -res + (2 * res * (x) / backend->width);
	const double	v = -1 + 2 * (backend->height - 1 - y) / backend->height;
	const double	k = u * fov / 2;

	return (v3d(sin(k), v, cos(k)));
}

#endif
