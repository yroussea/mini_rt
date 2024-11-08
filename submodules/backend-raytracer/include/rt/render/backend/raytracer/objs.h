/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 23:41:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H
# undef OBJS_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__

#  include <ft/math/vector.h>
#  include <ft/math/matrix.h>
#  include <rt/color.h>
#  include <rt/objects.h>
#  include <rt/render/backend/raytracer/ray.h>

//les objs seront pas a faire spown dans le backend !! temporaire uniquement
t_objs	*plane(t_vec3d normal, t_vec3d point, t_material m);
double	plane_intersect(t_ray *ray, t_vec3d normal, t_vec3d point);
t_objs	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam,
			t_vec3d colors);
t_objs	*sphere(t_vec3d center, double diameter, t_material m);
t_objs	*light(t_vec3d coo, double intensity, t_objs_type type, t_vec3d color);
t_objs	*camera(t_vec3d coo, t_vec3d view_vector, double fov);
t_objs	*cone(t_vec3d coo, t_vec3d vector, double height, double theta,
			t_vec3d colors);
t_objs	*add_objects(t_objs *new);

bool	rt_backend_raytracer_checkerboard(double a, double b);
t_vec3d	rt_backend_raytracer_planar_color(t_vec3d relative_hit, t_mat3d vectors,
			t_vec3d color, t_material_type type);
double	rt_backend_raytracer_planar_intersect(const t_ray *ray, t_vec3d n,
			t_vec3d a);

double	rt_backend_raytracer_cylinder_intersection(
			t_ray *ray, void *obj);
double	rt_backend_raytracer_cone_intersection(
			t_ray *ray, void *obj);

# endif // __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__
#endif // OBJS_H
