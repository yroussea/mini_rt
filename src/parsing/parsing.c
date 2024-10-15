/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:43:35 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/15 23:57:14 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <ft/math/vector.h>
#include <parsing.h>

int	is_rt_file(char *file)
{
	(void)file;
	return (1);
}

t_vec3d	rgb_to_vec(int r, int g, int b)
{
	return ((t_vec3d){(float)r/256, (float)g/256, (float)b/256});
}

void	parsing(char *file_scene)
{
	is_rt_file(file_scene);
	//...
	
	add_objects(plane((t_vec3d){0, 1, 0}, (t_vec3d){0, -50, 0}, (t_vec3d){0, 0, 1}));
	// add_objects(sphere((t_vec3d){0, 0, 0}, 10, (t_vec3d){1, 0, 0}));
	add_objects(cylinder((t_vec3d){0, 0, -20}, (t_vec3d){0, 0, 1}, 25, 25, (t_vec3d){0, 1, 0}));

	// add_objects(light((t_vec3d){0}, 0.1, AMBIANCE_LIGHT,(t_vec3d){1, 1, 1}));

	add_objects(camera((t_vec3d){0, 0, -100}, (t_vec3d){0, 0, 1}, 179));
	add_objects(light((t_vec3d){0, 100, -100}, 1, POINT_LIGHT, (t_vec3d){1, 1, 1}));

}
