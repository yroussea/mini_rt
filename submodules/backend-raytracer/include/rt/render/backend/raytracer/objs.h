/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:37:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 11:45:16 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H
# undef OBJS_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__

#  include <ft/math/vector.h>
#  include <rt/color.h>
#  include <rt/render/backend/raytracer/ray.h>

typedef struct s_plane
{
	t_vec3d	obj;
	t_vec3d	point;
	t_vec3d	normal;
}				t_plane;

typedef struct s_cylinder
{
	t_vec3d		center;
	t_vec3d		axis;
	float		diameter;
	float		height;
	t_vec3d		top_center;
	float		sq_radius;
}				t_cylinder;

typedef struct s_light
{
	t_vec3d			point;
	float			intensity;
}				t_light;

typedef struct s_sphere
{
	t_vec3d		center;
	float		rayon; //verif rayon ou diametre
	float		dot_production_rayon;
}				t_sphere;

typedef struct s_camera
{
	t_vec3d	point;
	t_vec3d	view_vector;
	float	fov;
}				t_camera;

typedef enum s_objs_type
{
	CAMERA = 1,
	AMBIANCE_LIGHT = 2,
	POINT_LIGHT = 3,
	OBJS = 4,
}			t_objs_type;

typedef struct s_objs
{
	void			*obj;
	t_objs_type		type;
	t_vec3d			colors; //separation?? materiaux/type/reflexion type t_vec3d pour utiliser operaion plus libre
	float			(*intersection)(t_ray ray, void *obj);
	t_vec3d			(*get_normal)(t_ray ray, void *obj);
	struct s_objs	*next;
}				t_objs;

//les objs seront pas a faire spown dans le backend !! temporaire uniquement
t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors);
float	plane_intersect(t_ray ray, t_vec3d normal, t_vec3d point);
t_objs	*cylinder(t_vec3d coo, t_vec3d vector, float height, float diam, t_vec3d colors);
t_objs	*sphere(t_vec3d center, float diameter, t_vec3d colors);
t_objs	*light(t_vec3d coo, float intensity, t_objs_type type, t_vec3d color);
t_objs	*camera(t_vec3d coo, t_vec3d view_vector, float fov);
t_objs	*add_objects(t_objs *new);



# endif // __RT_RENDER_BACKEND_RAYTRACER_OBJS_H__
#endif // OBJS_H
