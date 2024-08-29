#include <rt.h>
#include <object.h>
#include <math.h>

#define FOV 90

#define W_RES (4.f/3)
#define H_RES 1

extern float alpha;
extern float beta;

float	get_oposite(int fov)
{
	const float x = ((float)sqrt(pow(1/cos(fov * M_PI/360),2)-1));
	return (x);
}

t_v4f get_rotation(t_v4f point)
{
	t_v4f angle = (t_v4f){cos(alpha), sin(alpha), cos(beta), sin(beta)};
	return ((t_v4f){
		point[0]*angle[0] + point[1]*angle[1]*angle[3] - point[2]*angle[1]*angle[2],
		point[1]*angle[2] + point[2]*angle[3],
		point[0]*angle[1] - point[1]*angle[0]*angle[3] + point[2]*angle[0]*angle[2],
		0});
}

void	eye_rays(t_ray *ray, float u, float v)
{
	ray->direction = get_rotation((t_v4f){u, v, 1, 0});
	ray->point = ray->center + ray->direction;
	ray->color = (t_v4f){0,0,0,0};
}

float	get_width(float x)
{
	return (-W_RES * get_oposite(FOV) + (2 * W_RES * get_oposite(FOV))*(x)/WIDTH);
}
float	get_height(float y)
{
	return (-H_RES * get_oposite(FOV) + (2 * H_RES * get_oposite(FOV))*(HEIGHT - 1 - y)/HEIGHT);
}

