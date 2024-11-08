/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_find_obj_hit.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:33:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 14:28:59 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <ft/math/vector.h>
#include <math.h>

double	rt_backend_raytracer_find_obj_hit(t_ray *ray, t_objs *objs,
			t_objs **hit)
{
	double	distance_min;
	double	distance;

	distance_min = INFINITY;
	while (objs)
	{
		if (objs->type == OBJS)
		{
			distance = objs->intersection(ray, objs->obj);
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
