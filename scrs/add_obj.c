#include <object.h>
#include <rt.h>
#include <stdlib.h>
#include <maths.h>

void	add_sphere(t_objs **objs, t_v4f center, t_v4f rayon, t_v4f colors)
{
	t_objs		*new;
	t_sphere	*sph;

	sph = malloc(sizeof(t_sphere));
	sph->rayon = rayon;
	sph->center = center;
	sph->dot_production_rayon = dot_product(rayon * rayon);
	new = malloc(sizeof(t_objs));
	new->type = SPHERE;
	new->obj = sph;
	new->colors = colors;
	new->next = *objs;
	new->fcnt = ray_sphere_intersect;
	*objs = new;
}

void	add_triangle(t_objs **objs,t_v4f colors, t_v4f vertex1, t_v4f vertex2, t_v4f vertex3)
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
	new->next = *objs;
	new->normal = normalize(tri->normal);
	new->fcnt = ray_tri_intersect;
	*objs = new;
}

void	add_plane(t_objs **objs, t_v4f normal, t_v4f point, t_v4f colors)
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
	new->next = *objs;
	new->normal = normalize(normal);
	new->fcnt = ray_plane_intersect;
	*objs = new;
}

void	add_light(t_light **light, t_v4f coo, float intensity, t_light_type type, t_v4f color)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	if (type == NORMAL)
		new->point = coo;
	new->next = *light;
	new->intensity = intensity;
	new->color = color;
	new->type= type;
	*light = new;
}

void	add_objects_lights(t_objs **objs, t_light **lights)
{
	if (objs)
	{
		add_sphere(objs, (t_v4f){0, 0, 0, 0}, (t_v4f){12, 0, 0, 0}, BLUE);
		add_sphere(objs, (t_v4f){0, 0, 30, 0}, (t_v4f){20, 0, 0, 0}, RED);
		add_sphere(objs, (t_v4f){30, 0, 0, 0}, (t_v4f){10, 0, 0, 0}, WHITE);
		add_sphere(objs, (t_v4f){60, 0, 0, 0}, (t_v4f){15, 0, 0, 0}, WHITE);
		add_sphere(objs, (t_v4f){-150, 0, 100, 0}, (t_v4f){15, 0, 0, 0}, WHITE);
		// add_sphere(objs, (t_v4f){100, 180, 200, 0}, (t_v4f){20, 0, 0, 0}, GREEN);
		add_plane(objs, (t_v4f){0, 1, 0, 0}, (t_v4f){0, 25, 0, 0}, GREY);
		// add_triangle(objs, GREEN, (t_v4f){0, 0, 0, 0},
		// 		  (t_v4f){25, 0, 0, 0}, (t_v4f){0, 25, 0, 0});
		// add_triangle(objs, GREY,(t_v4f){0, 0, 0, 0},
		// 		  (t_v4f){-25, 0, 0, 0}, (t_v4f){0, -25, 0, 0});
		// add_triangle(objs, WHITE,(t_v4f){0, -25, -5, 0},
		// 		  (t_v4f){25, 0, -5, 0}, (t_v4f){0, 0, 0, 0});
		// add_triangle(objs, WHITE,(t_v4f){0, 0, 0, 0},
		// 		  (t_v4f){0, 25, -55, 0}, (t_v4f){-25, 0, -55, 0});
		t_objs *tmp = *objs;
		int		i = 0;
		while (tmp)
		{
			tmp->id = i++;
			tmp = tmp->next;
		}
	}
	if (lights)
	{
		// add_light(lights, (t_v4f){0, 0, -100, 0}, 1, NORMAL, WHITE);
		add_light(lights, (t_v4f){100, -100, -100, 0}, 1, NORMAL, WHITE);
		// add_light(lights, (t_v4f){0, -20, -100, 0}, 1, NORMAL, WHITE);
		add_light(lights, VEC0, 1, AMBIANCE, WHITE);
	}
}


