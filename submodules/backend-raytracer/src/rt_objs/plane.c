/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/26 18:21:41 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

static t_vec3d	get_plane_normal(t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;

	return (v3d_mult(plane->normal,
			-ft_fsign(v3d_dot(ray.direction, plane->normal))));
}

double	plane_intersect(t_ray ray, t_vec3d normal, t_vec3d point)
{
	return (v3d_dot(normal, v3d_sub(point, ray.point))
		/ v3d_dot(normal, ray.direction));
}

double	ray_plane_intersect(t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;

	return (plane_intersect(ray, plane->normal, plane->point));
}

#define SIZE_CHECKER 5
t_vec3d	get_colors_plane(t_ray ray, void *obj)
{
	const t_objs	*plane = (t_objs *)obj;
	const t_plane	*p_plane = (t_plane *)plane->obj;
	const t_vec3d	hit = ray.hit_point;

	(void)ray;
	if (plane->material.type == COLOR)
		return (plane->material.colors);
	const t_mat3d	mat = m3d(p_plane->vec_vdir, p_plane->vec_udir, p_plane->normal);
	const t_vec3d	x = m3d_solv(mat, v3d_sub(hit, p_plane->point));
	const double	a = fabs(floor(x.x / SIZE_CHECKER)) + fabs(floor(x.y  / SIZE_CHECKER));
	if ((int)a % 2)
		return ((t_vec3d){0, 0, 0});
	return (plane->material.colors);
}

t_objs	*plane(t_vec3d normal, t_vec3d point, t_material m)
{
	t_objs		*new;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	plane->normal = v3d_norm(normal);
	plane->vec_udir = v3d_norm(v3d(-plane->normal.y, plane->normal.x, 0));
	plane->vec_vdir = v3d_norm(v3d_cross(plane->normal, plane->vec_udir));
	plane->point = point;
	new = malloc(sizeof(t_objs));
	new->type = OBJS;
	new->obj = plane;
	new->material = m;
	new->get_normal = get_plane_normal;
	new->intersection = ray_plane_intersect;
	new->get_colors = get_colors_plane;
	return (new);
}
