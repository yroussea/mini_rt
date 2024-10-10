#ifndef SETUP_H
# define SETUP_H

# include <object.h>

typedef struct s_m_data
{
	void	*mlx;
	void	*wind;
	void	*img;
	void	(*draw_funct)(struct s_m_data *data);
}				t_m_data;

typedef enum s_setting
{
	NOTHING = 0,
	COLOR = 1,
	OBJS = 2,
	ALL = 3,
}			t_setting;

void	init_mlx(void func(t_m_data *));

void	get_colors(int ***color);
void	get_objs(t_objs	**objs);
void	free_scene_data(int **colors, t_objs *objs, int setting);
void	verify(int **colors, t_objs *objs, int setting);


void	destroy_mlx(t_m_data *data);
int		keyboard_clic(int keycode, void *data);

#endif
