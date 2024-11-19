/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_planar.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:51:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 04:39:41 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <rt/render/backend/raytracer.h>

double	rt_backend_raytracer_planar_intersect(
	const t_ray *ray,
	t_vec3d n,
	t_vec3d a
) {
	const t_vec3d	new_point = v3d_sub(&a, &ray->point);
	const double	numerator = v3d_dot(&n, &new_point);

	return (numerator / v3d_dot(&n, &ray->direction));
}

t_vec3d	rt_backend_raytracer_planar_color(
	t_vec3d relative_hit,
	t_mat3d vectors,
	t_rt_material material
) {
	const t_vec3d	all_colors[2] = {material.colors, material.check_colors};
	t_vec3d			solution;

	if (!(material.type & CHECKERBOARD))
		return (*all_colors);
	solution = m3d_solv(vectors, relative_hit);
	return (all_colors[rt_backend_raytracer_checkerboard(
				solution.z, solution.y)]);
}
