/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:39:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/09 00:48:10 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# undef OBJECTS_H
# ifndef __RT_OBJECTS_H__
#  define __RT_OBJECTS_H__

#  include <ft/math/vector.h>
#  include <ft/math/matrix.h>
#  include <rt/color.h>
#   include <rt/render/backend/raytracer/ray.h> //FIXME: remove this

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
}				t_plane
__attribute__((aligned(1)));

typedef struct s_cylinder
{
	t_vec3d				center;
	t_vec3d				axis;
	t_vec3d				vec_udir;
	t_vec3d				vec_vdir;
	t_vec3d				top_center;
	double				sq_radius;
	double				diameter;
	double				height;
	t_surface_hit_type	surface_type;
}				t_cylinder
__attribute__((aligned(1)));

typedef struct s_cone
{
	t_vec3d				center;
	t_vec3d				axis;
	t_vec3d				vec_udir;
	t_vec3d				vec_vdir;
	double				height;
	double				theta;
	double				cos;
	double				tan;
	double				max_dist;
	t_surface_hit_type	surface_type;
}				t_cone
__attribute__((aligned(1)));

typedef struct s_light
{
	t_vec3d			point;
	double			intensity;
}				t_light
__attribute__((aligned(1)));

typedef struct s_sphere
{
	t_vec3d		center;
	double		rayon; //verif rayon ou diametre
	double		dot_production_rayon;
}				t_sphere
__attribute__((aligned(1)));

typedef struct s_camera
{
	t_vec3d	point;
	t_vec3d	view_vector;
	double	fov;
}				t_camera
__attribute__((aligned(1)));

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
}			t_material
__attribute__((aligned(1)));

typedef struct s_objs
{
	void				*obj;
	t_objs_type			type;
	t_material			material;
	double				(*intersection)(t_ray *ray, void *obj);
	t_vec3d				(*get_normal)(const t_ray ray, void *obj);
	t_vec3d				(*get_colors)(const t_ray ray, void *obj);
	struct s_objs		*next;
}				t_objs;

# endif // __RT_OBJECTS_H__
#endif // OBJECTS_H
