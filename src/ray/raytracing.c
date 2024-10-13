/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:12:26 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 21:33:30 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include "object.h"
#include <maths.h>
#include <math.h>
#include <stdlib.h>

float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit)
{
	float	distance_min;
	float	distance;
	t_objs	*hit;

	hit = NULL;
	distance_min = INFINITY;
	while (objs)
	{
		if (objs->type & OBJS_MASK)
		{
			distance = objs->intersection(*ray, objs->obj);
			if (distance > 0 && distance < distance_min)
			{
				distance_min = distance;
				hit = objs;
				ray->hit_point = ft_vec3d_add(ray->point,
						ft_vec3d_mult(ray->direction, distance));
			}
		}
		objs = objs->next;
	}
	if (objs_hit)
		*objs_hit = hit;
	return (distance_min);
}



#define COEF_DIFFUSE 0.5
#define COEF_SPECULAR 0.5
#define COEF_EXPOS_SPECULAR 20

float	phong(t_ray ray, t_light *light, t_ray tmp, t_vec3d normal)
{
	t_vec3d	l;
	t_vec3d	h;

	l = ft_vec3d_norm(ft_vec3d_sub(light->point, tmp.center));
	h = ft_vec3d_norm(ft_vec3d_sub(tmp.direction, ray.direction));
	return (COEF_DIFFUSE * light->intensity * ft_fmax(-ft_vec3d_dot(normal, l), ft_vec3d_dot(normal, l)) +
		COEF_SPECULAR * light->intensity * pow(ft_fmax(-ft_vec3d_dot(normal, h), ft_vec3d_dot(normal, h)), COEF_EXPOS_SPECULAR));
}

#include <stdio.h>
#define EPSILON 1e-2
t_vec3d	shading(t_objs *objs, t_ray *ray, t_objs *objs_hit, t_vec3d normal)
{
	(void)normal;
	t_ray	tmp;
	t_vec3d	color;
	float	dist;
	t_light	*light;

	tmp.center = ray->hit_point;
	color = (t_vec3d){0, 0, 0};
	while (objs->type & LIGHT_MASK)
	{
		if (objs->type == AMBIANCE_LIGHT)
		{
			color = ft_vec3d_add(color, ft_vec3d_mult(objs->colors, light->intensity));
			objs = objs->next;
			continue ;
		}
		light = objs->obj;
		tmp.direction = ft_vec3d_norm(ft_vec3d_sub(light->point, tmp.center));
		tmp.point = ft_vec3d_add(tmp.center, ft_vec3d_mult(tmp.direction, EPSILON));
		dist = find_hit(&tmp, objs, NULL);
		if (dist > ft_vec3d_len(ft_vec3d_sub(tmp.point, light->point)))
			color = ft_vec3d_add(color, ft_vec3d_mult(objs->colors, phong(*ray, light, tmp, normal)));
		objs = objs->next;
	}
	return ((t_vec3d){color.x *objs_hit->colors.x,
		color.y *objs_hit->colors.y, color.z *objs_hit->colors.z});
}

void	get_shading(t_objs *objs, t_objs *obj_hit, t_ray *ray)
{
	if (!obj_hit || !(obj_hit->type & OBJS_MASK))
		return ;
	ray->color = shading(objs, ray, obj_hit, obj_hit->get_normal(*ray, obj_hit->obj));
}
