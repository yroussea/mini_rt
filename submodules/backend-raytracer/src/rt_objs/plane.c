/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 11:33:05 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

t_vec3d	get_plane_normal(t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;

	return (v3d_mult(plane->normal,
			-ft_fsign(v3d_dot(ray.direction, plane->normal))));
}

float	plane_intersect(t_ray ray, t_vec3d normal, t_vec3d point)
{
	return (v3d_dot(normal, v3d_sub(point, ray.point))
		/ v3d_dot(normal, ray.direction));
}

float	ray_plane_intersect(t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;

	return (plane_intersect(ray, plane->normal, plane->point));
}

t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors)
{
	t_objs		*new;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	plane->normal = v3d_norm(normal);
	plane->point = point;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = plane;
	new->colors = colors;
	new->get_normal = get_plane_normal;
	new->intersection = ray_plane_intersect;
	return (new);
}
