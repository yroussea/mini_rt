#include <rt.h>
#include <ray.h>
#include <stdlib.h>
#include <maths.h>
#include <threading.h>

void	one_pixel_ray(t_ray ray, int x, int y)
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
	if (find_hit(&ray, objs, &obj_hit) != INFINITY)
		get_shade(objs, lights, obj_hit, &ray, 0);
	pixel_color = vec_to_rgb(ray.color);
	for (int j = 0; j < PIXEL; j += 1)
	{
		for (int k = 0; k < PIXEL; k += 1)
			colors[y + j][x + k] = pixel_color;
	}
}

int	next_pixel(int *x, int *y)
{
	static int	k = 0;
	static int	j = 0;

	if (j == -1)
	{
		k = 0;
		j = 0;
		return (0);
	}
	*x = k;
	*y = j;
	k += PIXEL;
	if (k >= WIDTH)
	{
		k = 0;
		j += PIXEL;
	}
	if (j >= HEIGHT)
		j = -1;
	return (1);
}

#include <stdio.h>
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
	if (find_hit(&ray, objs, &obj) != INFINITY)
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


void	genering_image(t_m_data *m_data)
{
	static int			**colors = NULL;

	if (!colors)
		get_colors(&colors);
	all_image_ray();
	for (int y = 0; y < HEIGHT; y += 1)
	{
		for (int x = 0; x < WIDTH; x++)
			mlx_set_image_pixel(m_data->mlx, m_data->img, x, y, colors[y][x]);
	}
	mlx_put_image_to_window(m_data->mlx, m_data->wind, m_data->img, 0, 0);
}

#ifndef THREAD
void	all_image_ray()
{
	static t_ray		ray = {.center = (t_v4f){0, 0, -100, 0}};
	int					x = 0;
	int					y = 0;

	clock_t begin = clock();

	while (next_pixel(&x, &y))
		one_pixel_ray(ray, x, y);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Execution time: %.2f seconds\n", time_spent);
}
#else
void	all_image_ray()
{
	ray_th();
}
#endif
