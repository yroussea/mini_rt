/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:52:35 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/19 09:59:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

t_objs	*light(t_vec3d coo, float intensity, t_objs_type type, t_vec3d color)
{
	t_objs	*new;
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (type == POINT_LIGHT)
		light->point = coo;
	light->intensity = intensity;
	new = malloc(sizeof(t_objs));
	new->obj = light;
	new->colors = color;
	new->type = type;
	return (new);
}

t_objs	*camera(t_vec3d coo, t_vec3d view_vector, float fov)
{
	t_objs		*new;
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->fov = fov;
	cam->view_vector = view_vector;
	cam->point = coo;
	new = malloc(sizeof(t_objs));
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
