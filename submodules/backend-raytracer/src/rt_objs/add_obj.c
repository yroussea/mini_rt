/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:52:35 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/08 17:57:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <stdio.h>

t_vec3d	get_colors_light(t_ray ray, void *obj)
{
	const t_objs	*light = (t_objs *)obj;

	(void)ray;
	return (light->material.colors);
}

t_objs	*light(t_vec3d coo, double intensity, t_objs_type type, t_vec3d color)
{
	t_objs	*new;
	t_light	*light;

	light = rt_malloc_aligned(sizeof(t_light), 32);
	if (!light)
		return (NULL);
	if (type == POINT_LIGHT)
		light->point = coo;
	light->intensity = intensity;
	new = rt_malloc_aligned(sizeof(t_objs), 32);
	if (!new)
		rt_free_aligned(light);
	if (!new)
		return (NULL);
	new->obj = light;
	new->material = (t_material){COLOR, color};
	new->get_colors = get_colors_light;
	new->type = type;
	return (new);
}

t_objs	*camera(t_vec3d coo, t_vec3d view_vector, double fov)
{
	t_objs		*new;
	t_camera	*cam;

	cam = rt_malloc_aligned(sizeof(t_camera), 32);
	cam->fov = fov;
	cam->view_vector = view_vector;
	cam->point = coo;
	new = rt_malloc_aligned(sizeof(t_objs), 32);
	new->obj = cam;
	new->type = CAMERA;
	return (new);
}

t_objs	*add_objects(t_objs *new)
{
	static t_objs	*obj = NULL;
	t_objs			*tmp;

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
