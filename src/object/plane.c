#include "ft/math/vector.h"
#include <object.h>
#include <maths.h>
#include <stdlib.h>

t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors)
{
	t_objs		*new;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	plane->normal = ft_vec3d_norm(normal);
	plane->point = point;
	new = malloc(sizeof(t_objs));
	new->type = PLANE;
	new->obj = plane;
	new->colors = colors;
	new->get_normal = get_plane_normal;
	new->intersection = ray_plane_intersect;
	return (new);
}

t_vec3d	get_plane_normal(t_ray ray, void *obj)
{
	(void)ray;
	return (((t_plane *)obj)->normal);
}

float	ray_plane_intersect(t_ray ray, void *obj)
{
	t_plane	plane;

	plane = *(t_plane *)obj;
	return  (ft_vec3d_dot(plane.normal, ft_vec3d_sub(plane.point, ray.point)) \
				/ ft_vec3d_dot(plane.normal, ray.direction));
}
