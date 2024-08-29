/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:11:26 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/29 22:37:56 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>
#include <ray.h>
#include <rt.h>
#include <unistd.h>
#include <shading.h>

t_v4f	new_random_ray(t_v4f normal, t_v4f dire)
{
	return (2 * max(-dot_product(normal * dire), dot_product(normal * dire)) * normal - dire);
}

#define AMBIANCE_COEF 0.1
#define DISTANCE(x) ((float)(1/x*x))
#define EPSILON ((float)1e-2)
#include <stdio.h>
extern	int	debug;

t_v4f	lights_shading(t_objs *all_obj, t_light *light, t_ray ray, t_objs *objs_hit)
{
	t_ray	tmp;
	t_v4f	total_light = BLACK;
	float	dist_hit;

	tmp.center = ray.hit_point;
	while (light)
	{
		if (light->type == AMBIANCE)
		{
			total_light += (light->color) * (float)(light->intensity * AMBIANCE_COEF);
			light = light->next;
			continue ;
		}
		tmp.direction = normalize(light->point - tmp.center);
		tmp.point = tmp.center + tmp.direction * EPSILON;
		dist_hit = find_hit(&tmp, all_obj, NULL);
		if (debug) {printf("[%d->%f]\n", 0, dist_hit);}
		if (dist_hit > norm(tmp.point - light->point))
			total_light += light->color * phong(ray, light, tmp, objs_hit) * DISTANCE(dist_hit);
		if (debug) {
			printf("point %f %f %f \n",
		  tmp.point[0],
		  tmp.point[1],
		  tmp.point[2]
		  );
			printf("avant %f %f %f\n",
		  ray.direction[0],
		  ray.direction[1],
		  ray.direction[2]
		  );
			printf("apres %f %f %f \n",
		  tmp.direction[0],
		  tmp.direction[1],
		  tmp.direction[2]
		  );
			printf("hit %f %f %f \n",
		  tmp.direction[0] * dist_hit + tmp.point[0],
		  tmp.direction[1] * dist_hit + tmp.point[1],
		  tmp.direction[2] * dist_hit + tmp.point[2]
		  );
		}
		light = light->next;
	}
	return (total_light * objs_hit->colors);
}


t_v4f	shading(t_objs *all_obj, t_light *light, t_ray ray, t_objs *objs_hit, int depth)
{
	t_ray	tmp;
	t_v4f	total_light = BLACK;
	float	dist_hit;
	t_objs	*obj;

	total_light = lights_shading(all_obj, light, ray, objs_hit);
	tmp.center = ray.hit_point;
	tmp.color = VEC0;
	tmp.direction = new_random_ray(objs_hit->normal * sign(dot_product(objs_hit->normal * -ray.direction)), -ray.direction);
	tmp.point = tmp.center + tmp.direction * EPSILON;
	dist_hit = find_hit(&tmp, all_obj, &obj);
	if (dist_hit != INT_MAX)
	{
		(void)depth;
		get_shade(all_obj, light, obj, &tmp, depth + 1);
		if (debug) {printf("[%d->%d]\n", depth, obj->id);}
		total_light += tmp.color * DISTANCE(dist_hit);
	}
	return (total_light);
}

