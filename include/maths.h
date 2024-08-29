#ifndef MATHS_H
# define MATHS_H

# include <object.h>
# include <math.h>

typedef float	__attribute__((aligned(16),	vector_size(16)))	t_v4f;

t_v4f	normalize(t_v4f vector);
float	norm(t_v4f vector);

t_v4f	mult_vector(t_v4f a, t_v4f b);
float	dot_product(t_v4f v1);
t_v4f	cramer_rule_2d(t_v4f ab, t_v4f c_);
float	det2d(t_v4f abcd);
t_v4f	cross(t_v4f v1, t_v4f v2);

float	ray_tri_intersect(t_ray ray, void *obj);
float	ray_plane_intersect(t_ray ray, void *obj);
float	ray_sphere_intersect(t_ray ray, void *obj);

float	sign(float x);
float	max(float a, float b);
float	min(float a, float b);

int		vec_to_rgb(t_v4f v);
t_v4f	capped_vector(t_v4f v);

#endif
