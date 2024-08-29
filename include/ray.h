#ifndef RAY_H
# define RAY_H

# include <object.h>
# include <setup.h>

float	get_height(float y);
float	get_width(float x);
void	eye_rays(t_ray *ray, float u, float v);

float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit);
void	get_shade(t_objs *objs, t_light *lights, t_objs *obj, t_ray *ray, int depth);

void	single_ray(int x, int y);

void	genering_image(t_m_data *m_data);
void	all_image_ray();

#endif
