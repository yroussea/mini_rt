#include "ft/math/vector.h"
#include "mlx.h"
#include "object.h"
#include "rt.h"
#include <ray.h>
#include <stdio.h>
#include <stdlib.h>
// #include <rt.h>
// #include <maths.h>


void	lauch_one_ray(t_ray ray, int x, int y)
{
	(void)ray;
	(void)x;
	(void)y;
}

// void	set_pixel(int x, int y, int size)
// {
// static int **colors -> remplire les couleur
// }

void	ray_launching(t_objs *obj, void one_ray(t_ray ray, int x, int y))
{
	t_camera	*cam;
	t_ray		ray;
	int			x;
	int			y;

	cam = obj->obj;
	ray.center = cam->point;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			one_ray(ray, x, y);
			x += cam->pixelisation;
		}
		y += cam->pixelisation;
	}
}

void	gen_image(t_m_data *m_data)
{
	static int	**colors = NULL;
	int			x;
	int			y;

	if (!colors)
		get_colors(&colors);
	m_data->lauch_all_ray(get_cam(), m_data->lauch_one_ray);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_set_image_pixel(m_data->mlx, m_data->img, x, y, colors[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(m_data->mlx, m_data->wind, m_data->img, 0, 0);
}


