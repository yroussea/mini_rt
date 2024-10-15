#include "ft/math/vector.h"
#include <object.h>
#include <maths.h>
#include <math.h>
#include <stdlib.h>

float	closer(float t1, float t2)
{
	if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
		return (t1);
	return (t2);
}

float	ray_sphere_intersect(t_ray ray, void *obj)
{
	t_vec3d	v;
	float	b;
	float	a;
	float	delta;

	v = ft_vec3d_sub(ray.point, (*(t_sphere *)obj).center);
	b = ft_vec3d_dot(v, ray.direction);
	a = ft_vec3d_dot(ray.direction, ray.direction);
	delta = pow(b, 2) - a * \
		((ft_vec3d_dot(v, v) - (*(t_sphere *)obj).dot_production_rayon));
	if (delta >= 0)
		return (closer((-b + sqrtf(delta)) / a, (-b - sqrtf(delta)) / a));
	return (-1);
}

t_vec3d	get_sphere_normal(t_ray ray, void *obj)
{
	return (ft_vec3d_norm(ft_vec3d_sub(ray.hit_point, (*(t_sphere *)obj).center)));
}

t_objs	*sphere(t_vec3d center, float rayon, t_vec3d colors)
{
	t_objs		*new;
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	sph->rayon = rayon;
	sph->dot_production_rayon = rayon * rayon;
	sph->center = center;
	new = malloc(sizeof(t_objs));
	new->type = SPHERE;
	new->obj = sph;
	new->colors = colors;
	new->get_normal = get_sphere_normal;
	new->intersection = ray_sphere_intersect;
	return (new);
}
