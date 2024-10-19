/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_shading.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:47:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 02:29:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <ft/math/vector.h>
#include <ft/math.h>
#include <math.h>

// devrons etre dans une struct?
#define COEF_DIFFUSE 0.5
#define COEF_SPECULAR 0.5
#define COEF_EXPOS_SPECULAR 5

static float	phong_shading(t_ray ray, t_light *light,
					t_ray tmp, t_vec3d normal)
{
	t_vec3d	l;
	t_vec3d	h;

	l = v3d_norm(v3d_sub(light->point, tmp.center));
	h = v3d_norm(v3d_sub(tmp.direction, ray.direction));
	return (COEF_DIFFUSE * light->intensity * ft_fmax(0,
			v3d_dot(normal, l)) + COEF_SPECULAR * light->intensity
		* powf(ft_fmax(0, v3d_dot(normal, h)), COEF_EXPOS_SPECULAR));
}

__always_inline
static t_color	vec_to_color(t_vec3d light, t_vec3d obj_color)
{
	const t_color	color = {
		.r = 255 * ft_fmin(ft_fmax(0, light.x * obj_color.x), 1),
		.g = 255 * ft_fmin(ft_fmax(0, light.y * obj_color.y), 1),
		.b = 255 * ft_fmin(ft_fmax(0, light.z * obj_color.z), 1),
		.a = 255,
	};

	return (color);
}

t_color	shading(t_objs *objs, t_ray *ray, t_objs *obj_hit, t_vec3d normal)
{
	t_ray	tmp;
	t_vec3d	color;
	t_light	*light;

	tmp.center = ray->hit_point;
	color = (t_vec3d){0, 0, 0};
	while (objs->type != OBJS)
	{
		light = objs->obj;
		if (objs->type == AMBIANCE_LIGHT)
		{
			color = v3d_add(color, v3d_mult(objs->colors, light->intensity));
			objs = objs->next;
			continue ;
		}
		tmp.direction = v3d_norm(v3d_sub(light->point, tmp.center));
		tmp.point = v3d_add(tmp.center, v3d_mult(tmp.direction, EPSILON));
		if (rt_backend_raytracer_find_obj_hit(&tmp, objs, NULL) > \
			v3d_len(v3d_sub(tmp.point, light->point)))
			color = v3d_add(color, v3d_mult(objs->colors, \
						phong_shading(*ray, light, tmp, normal)));
		objs = objs->next;
	}
	return (vec_to_color(color, obj_hit->colors));
}

void	rt_backend_raytracer_get_shading(t_objs *objs, t_objs *obj_hit,
			t_ray *ray)
{
	(void)objs;
	ray->color = vec_to_color((t_vec3d){1,1,1}, obj_hit->colors);
	// ray->color = shading(objs, ray, obj_hit, \
					// obj_hit->get_normal(*ray, obj_hit->obj));
}
