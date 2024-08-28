/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:12:26 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/28 07:27:40 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>
#include <limits.h>
#include <maths.h>
#include <stdlib.h>
#include <rt.h>
#include <stdio.h>
#include <shading.h>


float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit)
{
	float	distance_min;
	float	distance;
	t_objs	*hit;

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
	if (objs_hit)
		*objs_hit = hit;
	return (distance_min);
}

void	get_shade(t_objs *objs, t_light *lights, t_objs *obj_hit, t_ray *ray, int depth)
{
	if (depth > 3)
		return ;
	if (obj_hit)
	{
		if (obj_hit->type & SPHERE)
			obj_hit->normal = normalize(ray->hit_point - (*(t_sphere *)obj_hit->obj).center);
		ray->color = shading(objs, lights, *ray, obj_hit, depth);
	}
}

void	single_ray(int x, int y)
{
	//debug only
	t_ray		ray;
	t_objs		*obj;
	static t_objs		*objs = NULL;
	static t_light		*lights = NULL;
	const	char		*t[3] = {"sphere", "plane", "tri"};

	if (!objs)
	{
		get_objs(&objs);
		get_lights(&lights);
	}
	ray.center = (t_v4f){0, 0, -100, 0};
	eye_rays(&ray, get_width((float)x), get_height((float)y));
	if (find_hit(&ray, objs, &obj) != INT_MAX)
	{
		printf("\tobject hit:\t[%d] \"%s\"\n\n",
		 obj->id, t[obj->type >> 1]);

		get_shade(objs, lights, obj, &ray, 0);

		printf("\t%scolor:\t\t%.02f %.02f %.02f%s\n", COLOR_YELLOW,
			ray.color[0], ray.color[1], ray.color[2], COLOR_RESET);
		printf("\thit_point:\t%.02f %.02f %.02f\n",
			ray.hit_point[0], ray.hit_point[1], ray.hit_point[2]);
	}
}


void	all_ray(t_m_data *m_data, __attribute__((unused)) int nb_frame)
{
	static int			**colors = NULL;

	if (!colors)
		get_colors(&colors);
	all_ray_once();
	for (int y = 0; y < HEIGHT; y += 1)
	{
		for (int x = 0; x < WIDTH; x++)
			mlx_set_image_pixel(m_data->mlx, m_data->img, x, y, colors[y][x]);
	}
	mlx_put_image_to_window(m_data->mlx, m_data->wind, m_data->img, 0, 0);
}

