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
		add_objects_lights(&objs, NULL);
	*x = objs;
}

void	get_lights(t_light	**x)
{
	static t_light	*light = NULL;

	if (!x)
		return ;
	if (!light)
		add_objects_lights(NULL, &light);
	*x = light;
}
