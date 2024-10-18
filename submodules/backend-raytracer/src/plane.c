/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/18 20:38:56 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

static float	sign(float x)
{
	if (x >= 0)
		return (1);
	return (-1);
}

t_vec3d	get_plane_normal(t_ray ray, void *obj)
{
	t_vec3d	normal;

	normal = ((t_plane *)obj)->normal;
	return (ft_vec3d_mult(normal, -sign(ft_vec3d_dot(ray.direction, normal))));
}

float	plane_intersect(t_ray ray, t_vec3d normal, t_vec3d point)
{
	return  (ft_vec3d_dot(normal, ft_vec3d_sub(point, ray.point)) \
				/ ft_vec3d_dot(normal, ray.direction));
}

float	ray_plane_intersect(t_ray ray, void *obj)
{
	t_plane	plane;

	plane = *(t_plane *)obj;
	return  (plane_intersect(ray, plane.normal, plane.point));
}

t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors)
{
	t_objs		*new;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	plane->normal = ft_vec3d_norm(normal);
	plane->point = point;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = plane;
	new->colors = colors;
	new->get_normal = get_plane_normal;
	new->intersection = ray_plane_intersect;
	return (new);
}
