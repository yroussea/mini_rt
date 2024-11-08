/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_plane.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 18:04:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

t_vec3d	rt_backend_raytracer_plane_normal(
	const t_ray ray, void *obj)
{
	const t_plane	*plane = (t_plane *)obj;
	const double	dot = v3d_dot(&ray.direction, &plane->normal);

	return (v3d_mult(&plane->normal, -ft_fsign(dot)));
}

double	rt_backend_raytracer_plane_intersection(
	t_ray *ray, void *obj)
{
	const t_plane	*p = (t_plane *)obj;

	return (rt_backend_raytracer_planar_intersect(ray, p->normal, p->point));
}

t_vec3d	rt_backend_raytracer_plane_color(
	const t_ray ray, void *obj)
{
	const t_objs	*plane = (t_objs *)obj;
	const t_plane	*p_plane = (t_plane *)plane->obj;

	return (rt_backend_raytracer_planar_color(
			v3d_sub(&ray.hit_point, &p_plane->point),
			m3d(p_plane->vec_vdir, p_plane->vec_udir, p_plane->normal),
			plane->material.colors,
			plane->material.type));
}

void	rt_backend_raytracer_plane(t_objs *obj)
{
	t_plane	*plane;
	t_vec3d	udir;
	t_vec3d	vdir;

	plane = obj->obj;
	udir = v3d(plane->normal.y + plane->normal.z,
			-plane->normal.x, -plane->normal.x);
	vdir = v3d_cross(&plane->normal, &udir);
	plane->vec_udir = v3d_norm(&udir);
	plane->vec_vdir = v3d_norm(&vdir);
	obj->get_normal = rt_backend_raytracer_plane_normal;
	obj->intersection = rt_backend_raytracer_plane_intersection;
	obj->get_colors = rt_backend_raytracer_plane_color;
}

t_objs	*plane(t_vec3d normal, t_vec3d point, t_material m)
{
	t_objs			*new;
	t_plane			*plane;

	plane = rt_malloc_aligned(sizeof(t_plane), 32);
	plane->normal = v3d_norm(&normal);
	plane->point = point;
	new = rt_malloc_aligned(sizeof(t_objs), 32);
	new->type = OBJS;
	new->obj = plane;
	new->material = m;
	rt_backend_raytracer_plane(new);
	return (new);
}
