#include <object.h>
#include <rt.h>
#include <stdlib.h>
#include <maths.h>

t_objs	*sphere(t_v4f center, t_v4f colors)
{
	t_objs		*new;
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	sph->rayon = center[3];
	sph->dot_production_rayon = center[3] * center[3];
	center[3] = 0;
	sph->center = center;
	new = malloc(sizeof(t_objs));
	new->type = SPHERE;
	new->obj = sph;
	new->colors = colors;
	new->fcnt = ray_sphere_intersect;
	return (new);
}

t_objs	*triangle(t_v4f colors, t_v4f vertex1, t_v4f vertex2, t_v4f vertex3)
{
	t_objs		*new;
	t_tri		*tri;
	t_v4f		a,b;

	tri = malloc(sizeof(t_tri));
	a = vertex2 - vertex1;
	b = vertex3 - vertex1;
	tri->normal = cross(a, b);
	tri->v1 = vertex1;
	tri->v2 = vertex2;
	tri->v3 = vertex3;
	new = malloc(sizeof(t_objs));
	new->type = TRIANGLE;
	new->obj = tri;
	new->colors = colors;
	new->normal = normalize(tri->normal);
	new->fcnt = ray_tri_intersect;
	return (new);
}

#include <stdio.h>
t_objs	*cylinder(t_v4f coo, t_v4f vector, float height, t_v4f colors)
{
	printf("cylinder on is way, dont try it (will destroy your code)\n");
	(void)coo;
	(void)vector;
	(void)height;
	(void)colors;
	return (NULL);
}

t_objs	*plane(t_v4f normal, t_v4f point, t_v4f colors)
{
	t_objs		*new;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	normal[3] = - normal[0]*point[0]- normal[1]*point[1]- normal[1]*point[1];
	plane->normal = normal;
	plane->point = point;
	new = malloc(sizeof(t_objs));
	new->type = PLANE;
	new->obj = plane;
	new->colors = colors;
	new->normal = normalize(normal);
	new->fcnt = ray_plane_intersect;
	return (new);
}

t_light *light(t_v4f coo, float intensity, t_light_type type, t_v4f color)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	if (type == NORMAL)
		new->point = coo;
	new->intensity = intensity;
	new->color = color;
	new->type= type;
	return (new);
}

void	add_objects_id(t_objs *objs)
{
	int		i = 0;
	while (objs)
	{
		objs->id = i++;
		objs = objs->next;
	}
}

t_objs	*add_objects(t_objs *new)
{
	static t_objs	*obj = NULL;

	if (new)
	{
		new->next = obj;
		new->reflexion = MIROIR;
		obj = new;
	}
	return (obj);
}

t_light	*add_lights(t_light *new)
{
	static t_light	*light = NULL;

	if (new)
	{
		new->next = light;
		light = new;
	}
	return (light);
}
