#include "object.h"
#include <rt.h>
#include <parsing.h>

int	is_rt_file(char *file)
{
	(void)file;
	return (1);
}

t_v4f	rgb_to_vec(int r, int g, int b)
{
	return ((t_v4f){(float)r/256, (float)g/256, (float)b/256, 0});
}

void	parsing(char *file_scene)
{
	is_rt_file(file_scene);
	//...
	
	//les spheres et cylindre ont on leur diametres dans le coo[3]
	add_objects(sphere((t_v4f){0, 0, 0, 12}, BLUE));
	add_objects(sphere((t_v4f){0, 0, 30, 20}, rgb_to_vec(255, 0, 0)));
	add_objects(sphere((t_v4f){60, 0, 0, 30}, WHITE));
	add_objects(plane((t_v4f){0, 1, 0, 0}, (t_v4f){0, -25, 0, 0}, GREY));

	add_lights(light((t_v4f){0, 100, -100, 0}, 1, NORMAL, WHITE));
	add_lights(light(VEC0, 1, AMBIANCE, WHITE));

}
