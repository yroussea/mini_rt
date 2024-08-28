#include <rt.h>
#include <object.h>
#include <math.h>

#define FOV 90

#define W_RES (4.f/3)
#define H_RES 1

float	get_oposite(int fov)
{
	const float x = ((float)sqrt(pow(1/cos(fov * M_PI/360),2)-1));
	return (x);
}

void	eye_rays(t_ray *ray, float u, float v)
{
	ray->direction = (t_v4f){u, v, 1, 0};
	ray->point = ray->center + ray->direction;
	ray->color = (t_v4f){0,0,0,0};
}

float	get_width(float x)
{
	return (-W_RES * get_oposite(FOV) + (2 * W_RES * get_oposite(FOV))*(x)/WIDTH);
}
float	get_height(float y)
{
	return (-H_RES * get_oposite(FOV) + (2 * H_RES * get_oposite(FOV))*(y)/HEIGHT);
}

