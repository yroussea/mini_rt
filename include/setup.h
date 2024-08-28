#ifndef SETUP_H
# define SETUP_H

# include <object.h>

typedef struct s_m_data
{
	void	*mlx;
	void	*wind;
	void	*img;
}				t_m_data;

typedef enum s_setting
{
	NOTHING = 0,
	COLOR = 1,
	OBJS = 2,
	LIGHT = 4,
	ALL = 7,
}			t_setting;

void	init_mlx();
void	free_all(int **colors, t_light *lights, t_objs *objs, int setting);
void	add_objects_lights(t_objs **objs, t_light **lights);
void	get_colors(int ***color);
void	get_objs(t_objs	**objs);
void	get_lights(t_light **lights);


#endif
