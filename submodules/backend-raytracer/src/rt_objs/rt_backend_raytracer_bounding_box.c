/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_bounding_box.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:00:21 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/09 17:34:45 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>
#include <math.h>

__attribute__((always_inline))
static t_vec3d	v3d_mult_v3d(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){.v = v1->v * v2->v});
}
__attribute__((always_inline))
static t_vec3d	v3d_min(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){
		.x = ft_fmin(v1->x, v2->x),
		.y = ft_fmin(v1->y, v2->y),
		.z = ft_fmin(v1->z, v2->z)});
}
__attribute__((always_inline))
static t_vec3d	v3d_max(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){
		.x = ft_fmax(v1->x, v2->x),
		.y = ft_fmax(v1->y, v2->y),
		.z = ft_fmax(v1->z, v2->z)});
}
__attribute__((always_inline))
static t_vec3d	v3d_opp(const t_vec3d *v1)
{
	return ((t_vec3d){.v = -v1->v});
}

bool	rt_backend_raytracer_bonding_box_intersection(
	const t_ray *ray, const t_bondingbox *bb)
{
	t_vec3d	tmin;
	t_vec3d	tmax;
	t_vec3d	t1;
	t_vec3d	t2;
	double	nearest_t;

	tmin = v3d_sub(&bb->mins, &ray->point);
	tmax = v3d_sub(&bb->maxs, &ray->point);
	tmin = v3d_mult_v3d(&tmin, &ray->inv_direction);
	tmax = v3d_mult_v3d(&tmax, &ray->inv_direction);
	t1 = v3d_min(&tmin, &tmax);
	t2 = v3d_max(&tmin, &tmax);
	nearest_t = ft_fmax(t1.x, ft_fmax(t1.y, t1.z));
	if (nearest_t < ft_fmin(t2.x, ft_fmin(t2.y, t2.z)) && nearest_t > 0)
		return (true);
	return (false);
}

t_vec3d	rt_be_rt_max_possitiv_value(t_mat3d v, t_vec3d s)
{
	return (v3d(
		ft_fabs(v.m[0][0] * s.x) + 
		ft_fabs(v.m[0][1] * s.y) + 
		ft_fabs(v.m[0][2] * s.z),
		ft_fabs(v.m[1][0] * s.x) + 
		ft_fabs(v.m[1][1] * s.y) + 
		ft_fabs(v.m[1][2] * s.z),
		ft_fabs(v.m[2][0] * s.x) + 
		ft_fabs(v.m[2][1] * s.y) + 
		ft_fabs(v.m[2][2] * s.z)));
}

bool	rt_backend_raytracer_creat_bonding_box(
	t_bondingbox **bb, t_vec3d center, t_mat3d vectors, t_vec3d sizes)
{
	t_vec3d	max;
	t_vec3d	min;

	*bb = rt_malloc_aligned(sizeof(t_bondingbox), 32);
	if (!*bb)
		return (false);
	max = rt_be_rt_max_possitiv_value(vectors, sizes);
	(*bb)->maxs = v3d_add(&center, &max);
	min = v3d_opp(&max);
	(*bb)->mins = v3d_add(&center, &min);
	return (true);
}
