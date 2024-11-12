/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:04:00 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/11 21:18:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H
# undef AABB_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_AABB_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_AABB_H__

#  include <rt/render/backend/raytracer/objects.h>

t_vec3d	rt_backend_raytracer_lowest_point_circle(const t_vec3d udir,
			const t_vec3d vdir, const t_vec3d center, const double diam);
t_vec3d	rt_backend_raytracer_highest_point_circle(const t_vec3d udir,
			const t_vec3d vdir, const t_vec3d center, const double diam);
void	rt_backend_raytracer_creating_aabbx(t_boundingbox **aabbx,
			const t_vec3d p1, const t_vec3d p2);
bool	rt_backend_raytracer_aabbx_inter(const t_ray *ray,
			const t_boundingbox *aabbx);

# endif // __RT_RENDER_BACKEND_RAYTRACER_AABB_H__
#endif // AABB_H
