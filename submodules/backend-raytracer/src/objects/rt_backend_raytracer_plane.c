/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_plane.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:14:34 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 16:58:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <rt/render/backend/raytracer.h>

t_vec3d	rt_backend_raytracer_plane_normal(
	const t_ray *ray,
	t_plane *plane
) {
	const double		dot = v3d_dot(&ray->direction, &plane->normal);
	const t_vec3d		normal = v3d_mult(&plane->normal, -ft_fsign(dot));
	const t_rt_material	mat = plane->base.material;
	t_vec3d				coo;

	if (mat.type & BUMP_MAP)
	{
		coo = m3d_solv(m3d(plane->vec_vdir, plane->vec_udir, plane->normal),
				v3d_sub(&ray->hit_point, &plane->point));
		return (rt_backend_raytracer_bumpmap(&normal, mat.bump.map,
				rt_backend_raytracer_bumpmap_coo(coo.x, coo.y, mat.bump.size)));
	}
	return (normal);
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
			plane->base.material));
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
