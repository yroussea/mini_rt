#include <rt.h>
#include <maths.h>

float	closer(float t1, float t2)
{
	if (t2 < 0 || (t2 > t1 && t1 > 0))
		return (t1);
	return (t2);
}


float	ray_sphere_intersect(t_ray ray, void *obj)
{
	t_sphere	*new = obj;
	t_sphere	sphere = *new;
	t_v4f v = ray.point - sphere.center;
	float b = dot_product(v * ray.direction);
	float a = dot_product(ray.direction * ray.direction);
	float delta;
	delta = pow(b, 2) - a * ((dot_product(v*v)- sphere.dot_production_rayon));
	if (delta >= 0)
	{
		float t1 = (-b + sqrtf(delta)) / a;
		float t2 = (-b - sqrtf(delta))/ a;
		return (closer(t1, t2));
	}
	return (-1);
}

float	ray_plane_intersect(t_ray ray, void *obj)
{
	t_plane	*new = obj;
	t_plane	plane = *new;
	float	t;
	t = dot_product(plane.normal * (plane.point - ray.point))/dot_product(plane.normal * ray.direction);
	return (t);
}

float	test_plane(t_ray ray, t_tri tri)
{
	t_plane a;

	a.normal = tri.normal;
	a.point = tri.v1;
	return (ray_plane_intersect(ray, &a));
}

float	ray_tri_intersect(t_ray ray, void *obj)
{
	t_tri	*new = obj;
	t_tri	tri = *new;
	t_v4f e1 = tri.v2 - tri.v1;
	t_v4f e2 = tri.v3 - tri.v1;
	float t = test_plane(ray, tri);

	if (t < 0)
		return (-1);
	t_v4f hit = t * ray.direction + ray.point - tri.v1;
	t_v4f uv_ = cramer_rule_2d((t_v4f){e1[0], e1[1], e2[0], e2[1]}, (t_v4f){hit[0], hit[1], 0, 0});
	if (uv_[0] < 0 || uv_[0] > 1)
		return (-1);
	if (uv_[1] < 0 || uv_[1] + uv_[0] > 1)
		return (-1);
	return (t);
}

