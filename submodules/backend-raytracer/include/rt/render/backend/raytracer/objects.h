/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/13 13:34:12 by yroussea         ###   ########.fr       */
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

//TODO: remove, swap into parser object provider
t_obj	*plane(t_vec3d normal, t_vec3d point, t_rt_material m);
t_obj	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam,
			t_vec3d colors);
t_obj	*sphere(t_vec3d center, double diameter, t_rt_material m);
t_obj	*light(t_vec3d coo, double intensity, t_rt_obj_type type, t_vec3d color);
t_obj	*camera(t_vec3d coo, t_vec3d view_vector, double fov);
t_obj	*cone(t_vec3d coo, t_vec3d vector, double height, double theta,
			t_vec3d colors);

double	plane_intersect(t_ray *ray, t_vec3d normal, t_vec3d point);
t_obj	*add_objects(t_obj *new);

bool	rt_backend_raytracer_checkerboard(double a, double b);
t_vec3d	rt_backend_raytracer_planar_color(t_vec3d relative_hit, t_mat3d vectors,
			t_vec3d color, t_rt_material_type type);
double	rt_backend_raytracer_planar_intersect(const t_ray *ray, t_vec3d n,
			t_vec3d a);

double	rt_backend_raytracer_cylinder_intersection(
			t_ray *ray, t_cylinder *cylinder);
double	rt_backend_raytracer_cone_intersection(
			t_ray *ray, t_cone *cone);

# endif // __RT_RENDER_BACKEND_RAYTRACER_OBJECTS_H__
#endif // OBJECTS_H
