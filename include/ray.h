#ifndef RAY_H
# define RAY_H

# include <object.h>
# include <mlx_manage.h>

void	gen_image(t_mdata *m_data);
void	ray_launching(t_objs *obj, void one_ray(t_ray ray, int x, int y));
void	lauch_one_ray(t_ray ray, int x, int y);

#endif
