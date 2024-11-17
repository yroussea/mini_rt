/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/17 17:40:03 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# undef OBJECTS_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_OBJECTS_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_OBJECTS_H__

#  include <ft/math/vector.h>
#  include <ft/math/matrix.h>
#  include <rt/color.h>
#  include <rt/objects.h>
#  include <rt/render/backend/raytracer/ray.h>

void	rt_backend_raytracer_cone_twod_relative_point(
	t_vec3d *relative_coo,
	const t_ray *ray,
	const t_cone *cone
);
t_vec3d	rt_backend_raytracer_colors_cone(
	const t_ray *ray,
	t_cone *cone
);
t_vec3d	rt_backend_raytracer_cone_normal(
	t_ray *ray,
	t_cone *cone
);
void	rt_backend_raytracer_cylinder_twod_relative_point(
	t_vec3d *relative_coo,
	const t_ray *ray,
	const t_cylinder *c_cy
);
t_vec3d	rt_backend_raytracer_colors_cylinder(
	const t_ray *ray,
	t_cylinder *cy
);
t_vec3d	rt_backend_raytracer_cylinder_normal(
	const t_ray *ray,
	t_cylinder *cy
);

double	plane_intersect(t_ray *ray, t_vec3d normal, t_vec3d point);
t_obj	*add_objects(t_obj *new);

t_vec3d	rt_backend_raytracer_bumpmap(
	const t_vec3d *vec,
	const t_vec3d *bump_color,
	const int coo);
int	rt_backend_raytracer_bumpmap_coo(
	const float u,
	const float v,
	const t_vec2i size);


bool	rt_backend_raytracer_checkerboard(double a, double b);
t_vec3d	rt_backend_raytracer_planar_color(t_vec3d relative_hit, t_mat3d vectors,
			t_rt_material material);
double	rt_backend_raytracer_planar_intersect(const t_ray *ray, t_vec3d n,
			t_vec3d a);

double	rt_backend_raytracer_cylinder_intersection(
			t_ray *ray, t_cylinder *cylinder);
double	rt_backend_raytracer_cone_intersection(
			t_ray *ray, t_cone *cone);

void	rt_backend_raytracer_cone(t_obj *obj);
void	rt_backend_raytracer_cylinder(t_obj *obj);
void	rt_backend_raytracer_plane(t_obj *obj);
void	rt_backend_raytracer_sphere(t_obj *obj);

# endif // __RT_RENDER_BACKEND_RAYTRACER_OBJECTS_H__
#endif // OBJECTS_H
