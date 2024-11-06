/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_planar.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:51:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/06 20:19:13 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>
#include <rt/render/backend/raytracer.h>

double	rt_backend_raytracer_planar_intersect(t_ray ray, t_vec3d n, t_vec3d a)
{
	const double	numerator = v3d_dot(n, v3d_sub(a, ray.point));

	return (numerator / v3d_dot(n, ray.direction));
}

t_vec3d	rt_backend_raytracer_planar_color(
	t_vec3d relative_hit, t_mat3d vectors, t_vec3d color, t_material_type type)
{
	const t_vec3d	all_colors[2] = {color, (t_vec3d){0, 0, 0}};
	t_vec3d			solution;

	if (type == COLOR)
		return (*all_colors);
	solution = m3d_solv(vectors, relative_hit);
	return (all_colors[rt_backend_raytracer_checkerboard(solution.x, solution.y)]);
}
