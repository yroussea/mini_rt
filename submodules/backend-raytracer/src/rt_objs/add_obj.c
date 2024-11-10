/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:52:35 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/10 11:56:42 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <stdio.h>

t_vec3d	get_colors_light(t_ray *ray, void *obj)
{
	const t_obj	*light = (t_obj *)obj;

	(void)ray;
	return (light->material.colors);
}

t_obj	*light(t_vec3d coo, double intensity, t_rt_obj_type type, t_vec3d color)
{
	t_obj	*new;
	t_light	*light;

	light = rt_malloc_aligned(sizeof(t_light), 32);
	if (!light)
		return (NULL);
	if (type == POINT_LIGHT)
		light->point = coo;
	light->intensity = intensity;
	new = (t_obj *) light;
	new->material = (t_rt_material){COLOR, {color}};
	new->calc_color = get_colors_light;
	new->type = type;
	return (new);
}

t_obj	*camera(t_vec3d coo, t_vec3d view_vector, double fov)
{
	t_obj		*new;
	t_camera	*cam;

	cam = rt_malloc_aligned(sizeof(t_camera), 32);
	cam->fov = fov;
	cam->view_vector = view_vector;
	cam->point = coo;
	new = (t_obj *) cam;
	new->type = CAMERA;
	return (new);
}

t_obj	*add_objects(t_obj *new)
{
	static t_obj	*obj = NULL;
	t_obj			*tmp;

	if (new)
	{
		new->next = NULL;
		tmp = obj;
		while (tmp && tmp->next && tmp->next->type < new->type)
			tmp = tmp->next;
		if (tmp && tmp->type < new->type)
		{
			new->next = tmp->next;
			tmp->next = new;
		}
		else
		{
			new->next = tmp;
			obj = new;
		}
	}
	return (obj);
}
