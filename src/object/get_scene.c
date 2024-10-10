/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:18:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/10 20:21:15 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <rt.h>
#include <setup.h>
#include <stdlib.h>

void	get_colors(int ***x)
{
	static int	**colors = NULL;

	if (!x)
		return ;
	if (!colors)
	{
		colors = malloc(sizeof(int *) * HEIGHT);
		if (!colors)
		{
			*x = NULL;
			return ;
		}
		for (int y = 0; y < HEIGHT; y += 1)
		{
			colors[y] = calloc(sizeof(int), WIDTH);
			if (!colors[y])
			{
				for (int k = 0; k < y; k += 1)
					free(colors[k]);
				free(colors);
				*x = NULL;
				return ;
			}
		}
	}
	*x = colors;
}

void	get_objs(t_objs	**x)
{
	static t_objs	*objs = NULL;

	if (!x)
		return ;
	if (!objs)
		objs = add_objects(NULL);
	*x = objs;
}

void	free_scene_data(int **colors, t_objs *objs, int setting)
{
	t_objs	*obj;

	if (setting & COLOR && colors)
	{
		for (int k = 0; k < HEIGHT; k += 1)
			free(colors[k]);
		free(colors);
		colors = NULL;
	}
	while (setting & OBJS && objs)
	{
		obj = objs;
		objs = objs->next;
		free(obj->obj);
		free(obj);
	}
	exit(setting + 1);
}

void	verify(int **colors, t_objs *objs, int setting)
{
	if (setting & OBJS && !objs)
		free_scene_data(colors, objs, COLOR);
	if (setting & COLOR && !colors)
		free_scene_data(colors, objs, NOTHING);
}
