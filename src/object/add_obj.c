#include <object.h>
#include <maths.h>
#include <stdlib.h>

#include <assert.h> // autoriser ?
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
	t_objs			*tmp;

	if (new)
	{
		new->id = id++;
		tmp = obj;
		while (tmp && tmp->next && tmp->next->type < new->type)
			tmp = tmp->next;
		if (tmp && tmp->type < new->type)
		{
			new->next = tmp->next;
			tmp->next = new;
		}
		else
		{
			new->next = tmp;
			obj = new;
		}
	}
	return (obj);
}
