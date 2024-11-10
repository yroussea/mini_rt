/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:16:24 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/10 12:53:16 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# undef UTILS_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_UTILS_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_UTILS_H__

#  include <ft/math/vector.h>
#  include <ft/math/matrix.h>
#  include <stddef.h>

double	rt_fmod(double x, double y);

t_mat3d	m3d(t_vec3d col1, t_vec3d col2, t_vec3d col3);
t_vec3d	m3d_solv(t_mat3d a, t_vec3d b);

void	*rt_malloc_aligned(size_t size, size_t alignment);
void	rt_free_aligned(void *ptr);

t_vec3d	v3d_inv(const t_vec3d *v);
t_vec3d	v3d_opp(const t_vec3d *v1);
t_vec3d	v3d_max(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d	v3d_min(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d	v3d_mult_v3d(const t_vec3d *v1, const t_vec3d *v2);
t_vec3d	v3d_abs(const t_vec3d *v);


# endif // __RT_RENDER_BACKEND_RAYTRACER_UTILS_H__
#endif // UTILS_H
