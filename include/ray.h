#ifndef RAY_H
# define RAY_H

# include <object.h>
# include <mlx_manage.h>

void	ray_launching(t_objs *obj, void one_ray(t_objs *, t_ray , int , int ),
	ushort w_size, ushort h_size);
void	lauch_one_ray(t_objs *objs, t_ray ray, int x, int y);
void	gen_image(t_mdata *m_data);

#endif
