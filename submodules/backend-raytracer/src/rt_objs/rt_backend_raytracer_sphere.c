/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_sphere.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/13 13:40:36 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <stdlib.h>
#include <math.h>

static double	rt_backend_raytracer_sphere_intersect(
	t_ray *ray,
	t_sphere *sphere
) {
	const t_vec3d	v = v3d_sub(&ray->point, &sphere->center);
	const t_vec3d	param = {
		.x = v3d_dot(&ray->direction, &ray->direction),
		.y = v3d_dot(&v, &ray->direction),
		.z = v3d_dot(&v, &v) - sphere->dot_production_rayon
	};
	const double	delta = (param.y * param.y) - param.x * param.z;
	double			t1;
	double			t2;

	if (delta < 0)
		return (-1);
	t1 = (-param.y + sqrtf(delta)) / param.x;
	t2 = (-param.y - sqrtf(delta)) / param.x;
	if (t2 < EPSILON || (t2 > t1 && t1 > EPSILON))
		return (t1);
	return (t2);
}

static void	rt_backend_raytracer_sphere_twod_relative_point(
	t_vec3d *relative_coo,
	t_ray *ray,
	const t_sphere *sph
) {
	const t_vec3d	x = v3d_sub(&ray->hit_point, &(sph->center));

	relative_coo->x = ft_fsign(x.z) * acos(x.x / sqrt(x.x * x.x + x.z * x.z));
	relative_coo->y = acos(x.y / sph->rayon);
}

t_vec3d	rt_backend_raytracer_sphere_normal(
	t_ray *ray,
	t_sphere *sphere
) {
	t_vec3d			coo;

	if (sphere->material.type == BUMP_MAP)
	{
		rt_backend_raytracer_sphereere_twod_relative_point(&coo, ray, sphere);
		/*bump map
		get_pixel hex -> rgb
		bump = (r * 2 - 1, g * 2 - 1 g * 2 -1)
		normal *= bump */
	}
	return (v3d_normsub(&ray->hit_point, &sphere->center));
}

t_vec3d	rt_backend_raytracer_colors_sphere(
	t_ray *ray,
	t_sphere *sph
) {
	const t_vec3d	colors[2] = {sph->base.material.colors, (t_vec3d){0, 0, 0}};
	t_vec3d			tmp;

	if (sph->base.material.type == COLOR)
		return (*colors);
	rt_backend_raytracer_sphere_twod_relative_point(&tmp, ray, sph);
	return (colors[rt_backend_raytracer_checkerboard(tmp.x * 50, tmp.y * 50)]);
}

void	rt_backend_raytracer_sphere(t_obj *obj)
{
	t_sphere	*sph;

	sph = (t_sphere *)obj;
	sph->dot_production_rayon = sph->rayon * sph->rayon;
	obj->calc_color = rt_backend_raytracer_colors_sphere;
	obj->calc_normal = rt_backend_raytracer_sphere_normal;
	obj->intersect = rt_backend_raytracer_sphere_intersect;
}

t_obj	*sphere(t_vec3d center, double diameter, t_rt_material material)
{
	t_obj		*new;
	t_sphere	*sph;

	sph = rt_malloc_aligned(sizeof(t_sphere), 32);
	sph->rayon = diameter / 2;
	sph->center = center;
	new = (t_obj *) sph;
	new->type = OBJS;
	new->material = material;
	rt_backend_raytracer_sphere(new);
	return (new);
}
