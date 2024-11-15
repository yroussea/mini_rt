/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_sphere.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 09:50:47 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/15 23:16:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt/objects.h"
#include "rt/render/backend/raytracer/objects.h"
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

#define RT_SCALE_BUMPMAP 1
int	rt_backend_raytracer_bumpmap_coo(
	const float u,
	const float v,
	const t_vec2i size)
{ 
	return ((int)(v * RT_SCALE_BUMPMAP) % size.x + \
		 ((int)(u * RT_SCALE_BUMPMAP) % size.y) * size.x);
}

t_vec3d	rt_backend_raytracer_bumpmap(
	const t_vec3d *vec,
	const t_vec3d *bump_color,
	const int coo)
{
	static const t_vec3d	diff = (t_vec3d){-1, -1, -1};
	const t_vec3d			rgb = bump_color[coo];
	const t_vec3d			bump = v3d_addmult(&diff, &rgb, 2);

	return (v3d_mult_v3d(vec, &bump));
}

t_vec3d	rt_backend_raytracer_sphere_normal(
	t_ray *ray,
	t_sphere *sphere
) {
	t_vec3d				coo;
	const t_rt_material	mat = sphere->base.material;
	const t_vec3d		normal = v3d_normsub(&ray->hit_point, &sphere->center);

	if (mat.type & BUMP_MAP)
	{
		rt_backend_raytracer_sphere_twod_relative_point(&coo, ray, sphere);
		return (rt_backend_raytracer_bumpmap(&normal, mat.bumpmap,
				rt_backend_raytracer_bumpmap_coo(coo.x, coo.y, mat.map_size)));
	}
	return (normal);
}

t_vec3d	rt_backend_raytracer_colors_sphere(
	t_ray *ray,
	t_sphere *sph
) {
	const t_vec3d	colors[2] = {sph->base.material.colors,
		sph->base.material.check_colors};
	t_vec3d			tmp;

	if (!(sph->base.material.type & CHECKERBOARD))
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
	new->type = OBJ_SPHERE;
	new->material = material;
	rt_backend_raytracer_sphere(new);
	return (new);
}
