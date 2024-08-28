#ifndef SHADING_H
# define SHADING_H

# include <object.h>

typedef float	__attribute__((aligned(16),	vector_size(16)))	t_v4f;

t_v4f	shading(t_objs *all_obj, t_light *light, t_ray ray, t_objs *objs_hit, int depth);
float	phong(t_ray ray, t_light *light, t_ray tmp, t_objs *objs_hit);

#endif
