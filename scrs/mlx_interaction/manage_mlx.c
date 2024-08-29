#include <setup.h>
#include <rt.h>
#include <mlx.h>
#include <stdlib.h>
#include <threading.h>

#include <stdio.h>
void	destroy_mlx(t_m_data *data)
{
	static t_objs		*objs = NULL;
	static t_light		*lights = NULL;
	static int			**colors = NULL;

	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->wind);
	mlx_destroy_display(data->mlx);
	get_colors(&colors);
	get_objs(&objs);
	get_lights(&lights);
	free_scene_data(colors, lights, objs, ALL);
	exit(EXIT_SUCCESS);
}

void	_loop(t_m_data *data)
{
	mlx_on_event(data->mlx, data->wind, MLX_KEYDOWN, keyboard_clic, data);
	printf("__%i__ (thread:%d)\n", 0, IS_THREADING * WORKER);
	data->draw_funct(data);
	mlx_loop(data->mlx);
}

void	init_mlx(void func(t_m_data *))
{
	void		*mlx;
	void		*wind;
	void		*img;
	t_m_data	data;

	mlx = mlx_init();
	wind = mlx_new_window(mlx, WIDTH,HEIGHT, "name");
	img = mlx_new_image(mlx, WIDTH,HEIGHT);
	data = (t_m_data){mlx, wind, img, func};
	if (img == NULL)
	{ //???
		destroy_mlx(&data);
		return ;
	}
	_loop(&data);
}


