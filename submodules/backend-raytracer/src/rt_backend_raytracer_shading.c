/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_shading.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:47:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 15:30:10 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <ft/math/vector.h>
#include <ft/math.h>
#include <math.h>

#define COEF_DIFFUSE 0.5
#define COEF_SPECULAR 0.5
#define COEF_EXPOS_SPECULAR 5

__always_inline
static float	phong_shading(t_ray ray, t_light *light,
					t_ray tmp, t_vec3d normal)
{
	t_vec3d	l;
	t_vec3d	h;

	l = v3d_normsub(&light->point, &tmp.center);
	h = v3d_normsub(&tmp.direction, &ray.direction);
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
static t_vec3d	shading(t_objs *objs, t_ray *ray, t_vec3d normal)
{
	t_ray			tmp;
	t_light			*light;
	t_vec3d			color;
	t_vec3d			color_light;

	tmp.center = ray->hit_point;
	color = (t_vec3d){0, 0, 0};
	while (objs->type != OBJS)
	{
		light = objs->obj;
		tmp.direction = v3d_normsub(&light->point, &tmp.center);
		tmp.point = v3d_addmult(&tmp.center, &tmp.direction, EPSILON);
		if (rt_backend_raytracer_find_obj_hit(&tmp, objs, NULL) > \
			v3d_lensub(&tmp.point, &light->point))
		{
			color_light = objs->get_colors(tmp, objs);
			color = v3d_addmult(&color, &color_light, \
						phong_shading(*ray, light, tmp, normal));
		}
		objs = objs->next;
	}
	return (color);
}

void	rt_backend_raytracer_get_shading(t_objs *objs, t_objs *obj_hit,
			t_ray *ray)
{
	const t_vec3d	color_obj = obj_hit->get_colors(*ray, obj_hit);
	t_vec3d			ambiance_color;
	t_vec3d			color;
	t_vec3d			color_light;
	t_light			*light;

	ambiance_color = (t_vec3d){0, 0, 0};
	while (objs->type == AMBIANCE_LIGHT)
	{
		light = objs->obj;
		color_light = objs->get_colors(*ray, objs);
		ambiance_color = v3d_addmult(&ambiance_color,
				&color_light, light->intensity);
		objs = objs->next;
	}
	color = shading(objs, ray, obj_hit->get_normal(*ray, obj_hit->obj));
	ambiance_color = v3d_add(&ambiance_color, &color);
	ray->color = vec_to_color(ambiance_color, color_obj);
}
