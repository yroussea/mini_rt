/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:12:26 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:58:58 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>
#include <stdlib.h>

#include <stdio.h>
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
//
// void	get_shade(t_objs *objs, t_light *lights, t_objs *obj_hit, t_ray *ray, int depth)
// {
// 	if (depth > 4)
// 		return ;
// 	if (obj_hit)
// 	{
// 		if (obj_hit->type & SPHERE)
// 			obj_hit->normal = normalize(ray->hit_point - (*(t_sphere *)obj_hit->obj).center);
// 		ray->color = shading(objs, lights, *ray, obj_hit, depth);
// 	}
// }
