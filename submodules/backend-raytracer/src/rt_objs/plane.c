/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/07 00:16:31 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

t_vec3d	get_plane_normal(t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;
	const double	dot = v3d_dot(&ray.direction, &plane->normal);

	return (v3d_mult(&plane->normal, -ft_fsign(dot)));
}

double	plane_intersect(t_ray *ray, t_vec3d normal, t_vec3d point)
{
	const t_vec3d	relative_point = v3d_sub(&point, &ray->point);

	return (v3d_dot(&normal, &relative_point) / v3d_dot(&normal, &ray->direction));
}

double	ray_plane_intersect(t_ray *ray, void *obj)
{
	const t_plane	*p = (t_plane *)obj;

	return (rt_backend_raytracer_planar_intersect(ray, p->normal, p->point));
}

t_vec3d	get_colors_plane(t_ray ray, void *obj)
{
	const t_objs	*plane = (t_objs *)obj;
	const t_plane	*p_plane = (t_plane *)plane->obj;

	return (rt_backend_raytracer_planar_color(
		v3d_sub(&ray.hit_point, &p_plane->point),
		m3d(p_plane->vec_vdir, p_plane->vec_udir, p_plane->normal),
		plane->material.colors,
		plane->material.type
	));
}

t_objs	*plane(t_vec3d normal, t_vec3d point, t_material m)
{
	t_objs			*new;
	t_plane			*plane;
	const t_vec3d	udir = v3d(normal.y + normal.z, -normal.x, -normal.x);
	const t_vec3d	vdir = v3d_cross(&normal, &udir);

	plane = malloc(sizeof(t_plane));
	plane->normal = v3d_norm(&normal);
	plane->vec_udir = v3d_norm(&udir);
	plane->vec_vdir = v3d_norm(&vdir);
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
