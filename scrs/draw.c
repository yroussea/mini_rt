/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:36:24 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/28 09:18:59 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdlib.h>
#include <ray.h>
#include <setup.h>
#include <threading.h>

void	destroy_mlx(t_m_data *data)
{
	static t_objs		*objs = NULL;
	static t_light		*lights = NULL;
	static int			**colors = NULL;

	get_colors(&colors);
	get_objs(&objs);
	get_lights(&lights);
	mlx_loop_end(data->mlx);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->wind);
	mlx_destroy_display(data->mlx);
	free_all(colors, lights, objs, ALL);
	exit(EXIT_SUCCESS);
}

int	debug = 0;
#include <stdio.h>
int	keyboard_clic(int keycode, void *data)
{
	t_m_data	*m_data;

	m_data = data;
	if (keycode == 41)
	{
		destroy_mlx(m_data);
		return (0);
	}
	if (keycode == 20)
	{
		int x,y = 0;
		mlx_mouse_get_pos(m_data->mlx, &x, &y);
		printf("\033[2J\033[1;1H");
		printf("\t\t--- %d %d ---\n", x, y);
		debug = 1;
		single_ray(x, y);
		debug = 0;
	}
	return (1);
}

#include <stdio.h>
#include <time.h>


void	draw_all_pixel(t_m_data *data, int i)
{
	if (!IS_THREADING)
	{
		clock_t begin = clock();
		all_ray(data, i);
		clock_t end = clock();
		double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Execution time: %.2f seconds\n", time_spent);
	}
	else
		all_ray(data, i);
}

void	_loop(t_m_data *data)
{
	mlx_on_event(data->mlx, data->wind, MLX_KEYDOWN, keyboard_clic, data);
	printf("__%i__ (thread:%d)\n", 0, IS_THREADING * WORKER);
	draw_all_pixel(data, 0);
	mlx_loop(data->mlx);
}

void	init_mlx()
{
	void		*mlx;
	void		*wind;
	void		*img;
	t_m_data	data;

	mlx = mlx_init();
	wind = mlx_new_window(mlx, WIDTH,HEIGHT, "name");
	img = mlx_new_image(mlx, WIDTH,HEIGHT);
	data = (t_m_data){mlx, wind, img};
	if (img == NULL)
	{ //???
		destroy_mlx(&data);
		return ;
	}
	_loop(&data);
}

