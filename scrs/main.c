/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/28 08:06:55 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <setup.h>
#include <rt.h>
#include <stdlib.h>

void	free_all(int **colors, t_light *lights, t_objs *objs, int setting)
{
	t_objs	*obj;
	t_light	*light;

	if (setting & COLOR && colors)
	{
		for (int k = 0; k < HEIGHT; k += 1)
			free(colors[k]);
		free(colors);
	}
	while (setting & OBJS && objs)
	{
		obj = objs;
		objs = objs->next;
		free(obj);
	}
	while (setting & LIGHT && lights)
	{
		light = lights;
		lights = lights->next;
		free(light);
	}
	exit(setting + 1);
}

void	verify(int **colors, t_light *light, t_objs *objs, int setting)
{
	if (setting & LIGHT && !light)
		free_all(colors, light, objs, COLOR | OBJS);
	if (setting & OBJS && !objs)
		free_all(colors, light, objs, COLOR);
	if (setting & COLOR && !colors)
		free_all(colors, light, objs, NOTHING);
}

int	main()
{
	int			**colors = NULL;
	t_light		*light = NULL;
	t_objs		*objs = NULL;

	get_colors(&colors);
	verify(colors, light, objs, COLOR);
	get_objs(&objs);
	verify(colors, light, objs, COLOR | OBJS);
	get_lights(&light);
	verify(colors, light, objs, COLOR | OBJS | LIGHT);
	init_mlx();
	free_all(colors, light, objs, ALL);
}

