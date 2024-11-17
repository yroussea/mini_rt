/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_shading.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:47:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/17 21:54:56 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/print.h"
#include "rt/objects.h"
#include <rt/render/backend/raytracer.h>
#include <ft/math/vector.h>
#include <ft/math.h>
#include <math.h>

#define COEF_DIFFUSE 0.5
#define COEF_SPECULAR 0.5
#define COEF_EXPOS_SPECULAR 5

__always_inline
static float	phong_shading(t_ray *ray, t_light *light,
					t_ray *tmp, t_vec3d normal)
{
	t_vec3d	l;
	t_vec3d	h;

	l = v3d_normsub(&light->point, &tmp->point);
	h = v3d_normsub(&tmp->direction, &ray->direction);
	return (COEF_DIFFUSE * light->intensity * ft_fmax(0,
			v3d_dot(&normal, &l)) + COEF_SPECULAR * light->intensity
		* powf(ft_fmax(0, v3d_dot(&normal, &h)), COEF_EXPOS_SPECULAR));
}

__always_inline
static t_color	vec_to_color(t_vec3d light, t_vec3d obj_color)
{
	const t_color	color = {
		.a = 255,
		.r = 255 * ft_fmin(ft_fmax(0, light.z * obj_color.z), 1),
		.g = 255 * ft_fmin(ft_fmax(0, light.y * obj_color.y), 1),
		.b = 255 * ft_fmin(ft_fmax(0, light.x * obj_color.x), 1),
	};

	return (color);
}

__always_inline
static t_vec3d	rt_backend_raytracer_shade_ambiant(t_obj **objs, t_ray *ray)
{
	t_obj	*obj;
	t_light	*light;
	t_vec3d	ambiance_color;
	t_vec3d	color_light;

	ambiance_color = (t_vec3d){0, 0, 0};
	obj = *objs;
	while (obj && obj->type == OBJ_AMBIANT_LIGHT)
	{
		light = (t_light *) obj;
		color_light = obj->calc_color(ray, light);
		ambiance_color = v3d_addmult(&ambiance_color,
				&color_light, light->intensity);
		obj = obj->next;
	}
	*objs = obj;
	return (ambiance_color);
}

__always_inline
static t_vec3d	rt_backend_raytracer_shade_light(t_obj *obj, t_ray *ray,
					t_vec3d normal)
{
	t_ray			tmp;
	t_light			*light;
	t_vec3d			color;
	t_vec3d			color_light;

	tmp.center = ray->hit_point;
	color = (t_vec3d){0, 0, 0};
	while (obj && obj->type == OBJ_LIGHT)
	{
		light = (t_light *) obj;
		tmp.direction = v3d_normsub(&light->point, &tmp.center);
		tmp.point = v3d_addmult(&tmp.center, &tmp.direction, EPSILON);
		if (rt_backend_raytracer_find_obj_hit(&tmp, obj, NULL) > \
			v3d_lensub(&tmp.point, &light->point))
		{
			color_light = obj->calc_color(&tmp, light);
			color = v3d_addmult(&color, &color_light, \
						phong_shading(ray, light, &tmp, normal));
		}
		obj = obj->next;
	}
	return (color);
}

void	rt_backend_raytracer_get_shading(t_obj *objs, t_obj *obj_hit,
			t_ray *ray)
{
	const t_vec3d	color_obj = obj_hit->calc_color(ray, obj_hit);
	const t_vec3d	ambiant_color
		= rt_backend_raytracer_shade_ambiant(&objs, ray);
	const t_vec3d	light_color
		= rt_backend_raytracer_shade_light(objs, ray,
			obj_hit->calc_normal(ray, obj_hit));
	const t_vec3d	tmp_color = v3d_add(&ambiant_color, &light_color);

	ray->color = vec_to_color(tmp_color, color_obj);
}
