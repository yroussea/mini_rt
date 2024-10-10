#include <rt.h>
#include <ray.h>
#include <stdlib.h>
#include <maths.h>

void	one_pixel_ray(t_ray ray, int x, int y)
{
	static t_objs		*objs = NULL;
	static int			**colors = NULL;
	t_objs				*obj_hit;
	int					pixel_color;

	if (!colors)
	{
		get_colors(&colors);
		get_objs(&objs);
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

void	all_image_ray()
{
	static t_ray		ray = {.center = (t_v4f){0, 0, -100, 0}};
	int					x = 0;
	int					y = 0;

	while (next_pixel(&x, &y))
		one_pixel_ray(ray, x, y);

}
