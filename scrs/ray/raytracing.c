/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:12:26 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/30 00:33:42 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>
#include <limits.h>
#include <maths.h>
#include <stdlib.h>
#include <rt.h>
#include <stdio.h>
#include <shading.h>

extern	int	debug;
float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit)
{
	float	distance_min;
	float	distance;
	t_objs	*hit = NULL;

	distance_min = INT_MAX;
	while (objs)
	{
		distance = objs->fcnt(*ray, objs->obj);
		if (distance > 0 && distance < distance_min)
		{
			distance_min = distance;
			hit = objs;
			ray->hit_point = ray->point + distance * ray->direction;
		}
		objs = objs->next;
	}
	if (debug && hit) {printf("[%s %d]\n", __func__, hit->id);}
	if (objs_hit)
		*objs_hit = hit;
	return (distance_min);
}

void	get_shade(t_objs *objs, t_light *lights, t_objs *obj_hit, t_ray *ray, int depth)
{
	if (depth > 4)
		return ;
	if (obj_hit)
	{
		if (obj_hit->type & SPHERE)
			obj_hit->normal = normalize(ray->hit_point - (*(t_sphere *)obj_hit->obj).center);
		ray->color = shading(objs, lights, *ray, obj_hit, depth);
	}
}

