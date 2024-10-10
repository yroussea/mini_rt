#ifndef MATHS_H
# define MATHS_H

# include <math.h>
# include <ft/math/vector.h>
# include <ft/math.h>
# include <object.h>

int		vec_to_rgb(t_vec3d v);
t_vec3d	capped_vector(t_vec3d v);
float	sign(float x);

float	closer(float t1, float t2);
float	ray_sphere_intersect(t_ray ray, void *obj);
float	ray_plane_intersect(t_ray ray, void *obj);


#endif
