/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/06 23:23:11 by yroussea         ###   ########.fr       */
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
#  include <rt/render/backend/raytracer/ray.h>

typedef enum e_surface_hit_type
{
	RONDED,
	PLANE,
	SECOND_PLANE,
}	t_surface_hit_type;

typedef struct s_plane
{
	t_vec3d	obj;
	t_vec3d	point;
	t_vec3d	normal;
	t_vec3d	vec_udir;
	t_vec3d	vec_vdir;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3d		center;
	t_vec3d		axis;
	t_vec3d		vec_udir;
	t_vec3d		vec_vdir;
	double		diameter;
	double		height;
	t_vec3d		top_center;
	double		sq_radius;
	t_surface_hit_type	surface_type;
}				t_cylinder;

typedef struct s_cone
{
	t_vec3d		center;
	t_vec3d		axis;
	t_vec3d		vec_udir;
	t_vec3d		vec_vdir;
	double		height;
	double		theta;
	double		max_dist;
	double		cos;
	t_surface_hit_type	surface_type;
}				t_cone;

typedef struct s_light
{
	t_vec3d			point;
	double			intensity;
}				t_light;

typedef struct s_sphere
{
	t_vec3d		center;
	double		rayon; //verif rayon ou diametre
	double		dot_production_rayon;
}				t_sphere;

typedef struct s_camera
{
	t_vec3d	point;
	t_vec3d	view_vector;
	double	fov;
}				t_camera;

typedef enum e_objs_type
{
	CAMERA = 1,
	AMBIANCE_LIGHT = 2,
	POINT_LIGHT = 3,
	OBJS = 4,
}			t_objs_type;

typedef enum e_material_type
{
	COLOR,
	CHECKERBOARD,
	BUMP_MAP,
}			t_material_type;

typedef struct s_material
{
	t_material_type	type;
	t_vec3d			colors;
}			t_material;



typedef struct s_objs
{
	void				*obj;
	t_objs_type			type;
	t_material			material;
	double				(*intersection)(t_ray *ray, void *obj);
	t_vec3d				(*get_normal)(t_ray ray, void *obj);
	t_vec3d				(*get_colors)(t_ray ray, void *obj);
	struct s_objs		*next;
}				t_objs;

//les objs seront pas a faire spown dans le backend !! temporaire uniquement
t_objs	*plane(t_vec3d normal, t_vec3d point, t_material m);
double	plane_intersect(t_ray *ray, t_vec3d normal, t_vec3d point);
t_objs	*cylinder(t_vec3d coo, t_vec3d vector, double height, double diam, t_vec3d colors);
t_objs	*sphere(t_vec3d center, double diameter, t_material m);
t_objs	*light(t_vec3d coo, double intensity, t_objs_type type, t_vec3d color);
t_objs	*camera(t_vec3d coo, t_vec3d view_vector, double fov);
t_objs	*cone(t_vec3d coo, t_vec3d vector, double height, double theta, t_vec3d colors);
t_objs	*add_objects(t_objs *new);


bool	rt_backend_raytracer_checkerboard(double a, double b);
t_vec3d	rt_backend_raytracer_planar_color(
	t_vec3d relative_hit, t_mat3d vectors, t_vec3d color, t_material_type type);
double	rt_backend_raytracer_planar_intersect(t_ray *ray, t_vec3d n, t_vec3d a);

double	rt_backend_raytracer_cylinder_intersection(
	t_ray *ray, void *obj);



# endif // __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__
#endif // OBJS_H
