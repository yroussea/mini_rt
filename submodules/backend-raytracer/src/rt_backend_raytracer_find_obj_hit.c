/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_find_obj_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:33:37 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <math.h>

bool	rt_object_can_intersect(t_obj *obj)
{
	const t_rt_obj_type	type = obj->type;

	if (type == OBJ_CAMERA)
		return (false);
	if (type == OBJ_AMBIANT_LIGHT || type == OBJ_LIGHT)
		return (false);
	return (obj->intersect != NULL);
}

double	rt_backend_raytracer_find_obj_hit(t_ray *ray, t_obj *objs,
			t_obj **hit)
{
	double	distance_min;
	double	distance;

	distance_min = INFINITY;
	if (hit)
		*hit = NULL;
	while (objs)
	{
		if (rt_object_can_intersect(objs))
		{
			distance = objs->intersect(ray, objs);
			if (distance > 0 && distance < distance_min)
			{
				distance_min = distance;
				if (hit)
					*hit = objs;
				ray->hit_point = v3d_addmult(&ray->point, \
								&ray->direction, distance);
			}
		}
		objs = objs->next;
	}
	return (distance_min);
}
