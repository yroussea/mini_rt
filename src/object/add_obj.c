#include <object.h>
#include <maths.h>
#include <stdlib.h>

#include <assert.h> // autoriser ?
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
	new->intersection = ray_sphere_intersect;
	return (new);
}

#include <stdio.h>
t_objs	*cylinder(t_vec3d coo, t_vec3d vector, float height, t_vec3d colors)
{
	printf("cylinder on is way, dont try it (will destroy your code)\n");
	(void)coo;
	(void)vector;
	(void)height;
	(void)colors;
	return (NULL);
}

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
	new->intersection = ray_plane_intersect;
	return (new);
}

t_objs	*light(t_vec3d coo, float intensity, t_objs_type type, t_vec3d color)
{
	t_objs	*new;
	t_light	*light;

	assert (type & LIGHT_MASK); //
	light = malloc(sizeof(t_light));
	if (type == POINT_LIGHT)
		light->point = coo;
	light->intensity = intensity;
	new = malloc(sizeof(t_objs));
	new->obj = light;
	new->colors = color;
	new->type = type;
	return (new);
}

t_objs	*camera(t_vec3d coo, t_vec3d view_vector, float fov)
{
	t_objs		*new;
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->fov = fov;
	assert (fov > 0 && fov < 180);
	cam->view_vector = view_vector;
	cam->point = coo;
	cam->pixelisation = 1;
	new = malloc(sizeof(t_objs));
	new->obj = cam;
	new->type = CAMERA;
	return (new);
}

t_objs	*add_objects(t_objs *new)
{
	static t_objs	*obj = NULL;
	static int		id = 0;

	if (new)
	{
		new->next = obj;
		new->id = id++;
		obj = new;
	}
	return (obj);
}