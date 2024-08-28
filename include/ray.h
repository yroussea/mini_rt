#ifndef RAY_H
# define RAY_H

# include <object.h>
# include <setup.h>

# define B_LIGNE 5
# define SET_LIGNE(x) (x) << B_LIGNE
# define GET_LINE(x) (x >> B_LIGNE)
# define GET_ROW(x) (x & ((1 << B_LIGNE) - 1))

typedef enum s_ligne
{
	ONE_LINE = 1,
	TWO_LINE = 2,
	THREE_LINE = 3,
	FIRST = SET_LIGNE(1),
	SECOND = SET_LIGNE(2),
	THIRD = SET_LIGNE(3),
}			t_ligne;

float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit);
float	get_height(float y);
float	get_width(float x);
void	get_shade(t_objs *objs, t_light *lights, t_objs *obj, t_ray *ray, int depth);
void	all_ray(t_m_data *m_data, int i);
void	eye_rays(t_ray *ray, float u, float v);
void	all_ray_once();
void	one_ray(t_ray ray, int x, int y);
void	single_ray(int x, int y);

#endif
