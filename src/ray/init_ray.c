#include <rt.h>
#include <mlx_manage.h>
#include <object.h>
#include <math.h>

static float	get_oposite(char fov)
{
	float x = atan(fov / 2.);
	return (x);
}

void	eye_rays(t_ray *ray, float u, float v)
{
	ray->direction = /* get_rotation */(t_vec3d){u, v, 1};
	ray->point = ft_vec3d_add(ray->center, ray->direction);
	ray->color = (t_vec3d){0, 0, 0};
}

float	get_width(float x, char fov)
{
	return (-get_oposite(fov) + (2 * get_oposite(fov)) * (x) / WIDTH);
}

float	get_height(float y)
{
	return (-1 + 2 * (HEIGHT - 1 - y) / HEIGHT);
}
