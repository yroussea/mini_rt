#include <maths.h>

#define DIFFUSE_COEF 0.5
#define SPECULAR_COEF 0.5
#define SPECULAR_EXPOS 20

float	diffuse_light(float intensity, t_v4f n, t_v4f l)
{
	return (DIFFUSE_COEF * intensity * max(-dot_product(n * l), dot_product(n * l)));
}

float	specualar_shading(float intensity, t_v4f n, t_v4f h)
{
	return (SPECULAR_COEF * intensity * pow(max(-dot_product(n * h), dot_product(n * h)), SPECULAR_EXPOS));
}

float	calc_diffuse(t_light *light, t_ray tmp, t_objs *objs_hit)
{
	return (diffuse_light(light->intensity, objs_hit->normal, \
					   normalize(light->point - tmp.center)));
}

float	calc_specular(t_ray ray, t_light *light, t_ray tmp, t_objs *objs_hit)
{
	return (specualar_shading(light->intensity, objs_hit->normal, normalize(-ray.direction + tmp.direction)));
}

float	phong(t_ray ray, t_light *light, t_ray tmp, t_objs *objs_hit)
{
	return (calc_specular(ray, light, tmp, objs_hit) + calc_diffuse(light, tmp, objs_hit));
}
