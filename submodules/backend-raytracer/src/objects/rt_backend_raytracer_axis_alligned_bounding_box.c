/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_axis_alligned_bounding_b      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:20:30 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/17 19:46:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/render/backend/raytracer.h>

bool	rt_backend_raytracer_aabbx_inter(
	const t_ray *ray,
	const t_boundingbox *aabbx
) {
	t_vec3d	tmin;
	t_vec3d	tmax;
	t_vec3d	t1;
	t_vec3d	t2;
	double	nearest_t;

	if (!aabbx)
		return (true);
	tmin = v3d_sub(&aabbx->mins, &ray->point);
	tmax = v3d_sub(&aabbx->maxs, &ray->point);
	tmin = v3d_mult_v3d(&tmin, &ray->inv_direction);
	tmax = v3d_mult_v3d(&tmax, &ray->inv_direction);
	t1 = v3d_min(&tmin, &tmax);
	t2 = v3d_max(&tmin, &tmax);
	nearest_t = ft_fmax(t1.x, ft_fmax(t1.y, t1.z));
	if (nearest_t < ft_fmin(t2.x, ft_fmin(t2.y, t2.z)))
		return (true);
	return (false);
}

void	rt_backend_raytracer_creating_aabbx(
	t_boundingbox **aabbx, const t_vec3d p1, const t_vec3d p2)
{
	static const t_vec3d	error_margin = (t_vec3d){8, 8, 8};

	*aabbx = rt_malloc_aligned(sizeof(t_boundingbox), 32);
	if (!*aabbx)
		return ;
	(*aabbx)->maxs = v3d_max(&p1, &p2);
	(*aabbx)->maxs = v3d_add(&(*aabbx)->maxs, &error_margin);
	(*aabbx)->mins = v3d_min(&p1, &p2);
	(*aabbx)->mins = v3d_sub(&(*aabbx)->mins, &error_margin);
}

t_vec3d	rt_backend_raytracer_highest_point_circle(
	const t_vec3d udir,
	const t_vec3d vdir,
	const t_vec3d center,
	const double diam
) {
	t_vec3d	highest;
	t_vec3d	abs;

	highest = center;
	abs = v3d_abs(&udir);
	highest = v3d_addmult(&highest, &abs, diam);
	abs = v3d_abs(&vdir);
	highest = v3d_addmult(&highest, &abs, diam);
	return (highest);
}

t_vec3d	rt_backend_raytracer_lowest_point_circle(
	const t_vec3d udir,
	const t_vec3d vdir,
	const t_vec3d center,
	const double diam)
{
	t_vec3d	highest;
	t_vec3d	abs;

	highest = center;
	abs = v3d_abs(&udir);
	abs = v3d_opp(&abs);
	highest = v3d_addmult(&highest, &abs, diam);
	abs = v3d_abs(&vdir);
	abs = v3d_opp(&abs);
	highest = v3d_addmult(&highest, &abs, diam);
	return (highest);
}
