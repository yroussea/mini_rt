#ifndef RAY_H
# define RAY_H

# include <object.h>
# include <mlx_manage.h>

void	ray_launching(t_mdata *mdata, void one_ray(t_objs *, t_ray , int),
	ushort w_size, ushort h_size);
void	lauch_one_ray(t_objs *objs, t_ray ray, int x);
void	gen_image(t_mdata *m_data);

float	get_height(float y);
float	get_width(float x, char fov);
void	eye_rays(t_ray *ray, float u, float v);

float	find_hit(t_ray *ray, t_objs *objs, t_objs **objs_hit);
void	get_shading(t_objs *objs, t_objs *obj_hit, t_ray *ray);

#endif
