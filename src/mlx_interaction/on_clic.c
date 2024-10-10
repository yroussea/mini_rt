#include <rt.h>
#include <math.h>
#include <setup.h>
#include <ray.h>

float	alpha = 0;
float	beta = 0;
int		debug = 0;
#include <stdio.h>

static void	rotation(int keycode, t_m_data *data)
{
	(void)data;
	if (keycode == 80)
		alpha += M_PI * 0.1;
	if (keycode == 79)
		alpha -= M_PI * 0.1;
	if (keycode == 82)
		beta += M_PI * 0.1;
	if (keycode == 81)
		beta -= M_PI * 0.1;
}

static void	_exit_(t_m_data *data)
{
	destroy_mlx(data);
}

int	keyboard_clic(int keycode, void *data)
{
	t_m_data	*m_data;

	printf("(%d)\n",keycode);
	m_data = data;
	if (keycode == 41)
		_exit_(data);
	if (keycode == 20)
	{
		int x,y = 0;
		mlx_mouse_get_pos(m_data->mlx, &x, &y);
		printf("\t\t--- %d %d ---\n", x, y);
		debug = 1;
		single_ray(x, y);
		debug = 0;
	}
	rotation(keycode, data);
	m_data->draw_funct(data);
	return (1);
}

