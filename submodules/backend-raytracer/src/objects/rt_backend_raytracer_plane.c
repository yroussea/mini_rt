/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_plane.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/10 11:56:07 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

t_vec3d	rt_backend_raytracer_plane_normal(
	const t_ray *ray,
	t_plane *plane
) {
	const double	dot = v3d_dot(&ray->direction, &plane->normal);

	return (v3d_mult(&plane->normal, -ft_fsign(dot)));
}

double	rt_backend_raytracer_plane_intersection(
	t_ray *ray,
	t_plane *plane
) {
	return (rt_backend_raytracer_planar_intersect(ray, plane->normal,
			plane->point));
}

t_vec3d	rt_backend_raytracer_plane_color(
	const t_ray *ray,
	t_plane *plane
) {
	return (rt_backend_raytracer_planar_color(
			v3d_sub(&ray->hit_point, &plane->point),
			m3d(plane->vec_vdir, plane->vec_udir, plane->normal),
			plane->base.material.colors, plane->base.material.type));
}

void	rt_backend_raytracer_plane(t_obj *obj)
{
	t_plane	*plane;
	t_vec3d	udir;
	t_vec3d	vdir;

	plane = (t_plane *)obj;
	udir = v3d(plane->normal.y + plane->normal.z,
			-plane->normal.x, -plane->normal.x);
	vdir = v3d_cross(&plane->normal, &udir);
	plane->vec_udir = v3d_norm(&udir);
	plane->vec_vdir = v3d_norm(&vdir);
	obj->intersect = rt_backend_raytracer_plane_intersection;
	obj->calc_normal = rt_backend_raytracer_plane_normal;
	obj->calc_color = rt_backend_raytracer_plane_color;
}

t_obj	*plane(t_vec3d normal, t_vec3d point, t_rt_material m)
{
	t_obj	*new;
	t_plane	*plane;

	plane = rt_malloc_aligned(sizeof(t_plane), 32);
	plane->normal = v3d_norm(&normal);
	plane->point = point;
	new = (t_obj *) plane;
	new->type = OBJS;
	new->material = m;
	rt_backend_raytracer_plane(new);
	return (new);
}
