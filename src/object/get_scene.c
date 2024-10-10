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
	{
		objs = add_objects(NULL);
		add_objects_id(objs);
	}
	*x = objs;
}

void	get_lights(t_light	**x)
{
	static t_light	*light = NULL;

	if (!x)
		return ;
	if (!light)
		light = add_lights(NULL);
	*x = light;
}

void	free_scene_data(int **colors, t_light *lights, t_objs *objs, int setting)
{
	t_objs	*obj;
	t_light	*light;

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
		free_scene_data(colors, light, objs, COLOR | OBJS);
	if (setting & OBJS && !objs)
		free_scene_data(colors, light, objs, COLOR);
	if (setting & COLOR && !colors)
		free_scene_data(colors, light, objs, NOTHING);
}
