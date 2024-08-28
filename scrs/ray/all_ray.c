#include <rt.h>
#include <ray.h>
#include <stdlib.h>
#include <maths.h>
#include <threading.h>
#include <limits.h>

void	one_ray(t_ray ray, int x, int y)
{
	static t_objs		*objs = NULL;
	static t_light		*lights = NULL;
	static int			**colors = NULL;
	t_objs				*obj_hit;
	int					pixel_color;

	if (!colors)
	{
		get_colors(&colors);
		get_objs(&objs);
		get_lights(&lights);
	}
	eye_rays(&ray, get_width((float)x), get_height((float)y));
	if (find_hit(&ray, objs, &obj_hit) != INT_MAX)
		get_shade(objs, lights, obj_hit, &ray, 0);
	pixel_color = vec_to_rgb(ray.color);
	for (int j = 0; j < PIXEL; j += 1)
	{
		for (int k = 0; k < PIXEL; k += 1)
			colors[y + j][x + k] = pixel_color;
	}
}

int	next_pixel(int *x, int *y, t_ligne setting)
{
	static int	k = 0;
	static int	j = 0;

	if (j == -1)
	{
		k = 0;
		j = PIXEL * GET_LINE(setting);
		return (0);
	}
	*x = k;
	*y = j;
	k += PIXEL;
	if (k >= WIDTH)
	{
		k = 0;
		j += PIXEL * GET_ROW(setting);
	}
	if (j >= HEIGHT)
		j = -1;
	return (1);
}

#ifndef THREAD
void	all_ray_once()
{
	static t_ray		ray = {.center = (t_v4f){0, 0, -100, 0}};
	int					x = 0;
	int					y = 0;

	for (int k = 1; k <= ONE_LINE; k++)
	{
		while (next_pixel(&x, &y, k | SET_LIGNE(k)))
			one_ray(ray, x, y);
	}
}
#else
void	all_ray_once()
{
	ray_th();
}
#endif
