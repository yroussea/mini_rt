/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:34:18 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 16:29:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <object.h>
#include <maths.h>
#include <math.h>

static float	closer(float t1, float t2)
{
	if (t2 < 0 || (t2 > t1 && t1 > 0))
		return (t1);
	return (t2);
}

float	ray_sphere_intersect(t_ray ray, void *obj)
{
	t_vec3d	v;
	float	b;
	float	a;
	float	delta;

	v = ft_vec3d_sub(ray.point, (*(t_sphere *)obj).center);
	b = ft_vec3d_dot(v, ray.direction);
	a = ft_vec3d_dot(ray.direction, ray.direction);
	delta = pow(b, 2) - a * \
		((ft_vec3d_dot(v, v) - (*(t_sphere *)obj).dot_production_rayon));
	if (delta >= 0)
		return (closer((-b + sqrtf(delta)) / a, (-b - sqrtf(delta)) / a));
	return (-1);
}

float	ray_plane_intersect(t_ray ray, void *obj)
{
	t_plane	plane;

	plane = *(t_plane *)obj;
	return  (ft_vec3d_dot(plane.normal, ft_vec3d_sub(plane.point, ray.point)) \
				/ ft_vec3d_dot(plane.normal, ray.direction));
}
