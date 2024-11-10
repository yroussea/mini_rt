/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:39:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/10 13:06:34 by yroussea         ###   ########.fr       */
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

/** Default object definition **/

typedef enum e_rt_obj_type
{
	CAMERA = 0,
	AMBIANCE_LIGHT,
	POINT_LIGHT,
	OBJS, // TODO: change to individual types
}	t_rt_obj_type;

typedef enum e_rt_material
{
	COLOR = 0,
	CHECKERBOARD,
	BUMP_MAP,
}	t_rt_material_type;

typedef struct s_rt_material
{
	t_rt_material_type	type;
	union
	{
		t_vec3d			colors;
	};
}	t_rt_material;

// Note: all these functions take a `t_ray *` as their first param,
// and a `void *` as their second.
typedef double	(*t_ray_intersect_fn)();
typedef t_vec3d	(*t_ray_normal_fn)();
typedef t_vec3d	(*t_ray_color_fn)();

typedef struct s_obj
{
	t_rt_obj_type		type;
	t_rt_material		material;

	t_ray_intersect_fn	intersect;
	t_ray_normal_fn		calc_normal;
	t_ray_color_fn		calc_color;

	struct s_obj		*next;
}	t_obj;

typedef struct s_bondingbox
{
	t_vec3d	mins;
	t_vec3d	maxs;
}			t_boundingbox
__attribute__((aligned(1)));

typedef enum e_surface_hit_type
{
	RONDED,
	PLANE,
	SECOND_PLANE,
}	t_surface_hit_type;

typedef struct s_plane
{
	t_obj	base;
	t_vec3d	obj;
	t_vec3d	point;
	t_vec3d	normal;
	t_vec3d	vec_udir;
	t_vec3d	vec_vdir;
}	t_plane
__attribute__((aligned(1)));

typedef struct s_cylinder
{
	t_obj				base;
	t_vec3d				center;
	t_vec3d				axis;
	t_vec3d				vec_udir;
	t_vec3d				vec_vdir;
	t_vec3d				top_center;
	double				sq_radius;
	double				diameter;
	double				height;
	t_boundingbox		*aabbx;
	t_surface_hit_type	surface_type;
}	t_cylinder
__attribute__((aligned(1)));

typedef struct s_cone
{
	t_obj				base;
	t_vec3d				center;
	t_vec3d				axis;
	t_vec3d				vec_udir;
	t_vec3d				vec_vdir;
	double				height;
	double				theta;
	double				cos;
	double				tan;
	double				max_dist;
	t_boundingbox		*aabbx;
	t_surface_hit_type	surface_type;
}	t_cone
__attribute__((aligned(1)));

typedef struct s_light
{
	t_obj			base;
	t_vec3d			point;
	double			intensity;
}	t_light
__attribute__((aligned(1)));

typedef struct s_sphere
{
	t_obj		base;
	t_vec3d		center;
	double		rayon; //verif rayon ou diametre
	double		dot_production_rayon;
}	t_sphere
__attribute__((aligned(1)));

typedef struct s_camera
{
	t_obj	base;
	t_vec3d	point;
	t_vec3d	view_vector;
	double	fov;
}	t_camera
__attribute__((aligned(1)));

# endif // __RT_OBJECTS_H__
#endif // OBJECTS_H
