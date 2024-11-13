/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_additionnal_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:13:12 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/13 13:38:28 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math/vector.h>
#include <ft/math.h>

__attribute__((always_inline))
t_vec3d	v3d_min(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){
		.x = ft_fmin(v1->x, v2->x),
		.y = ft_fmin(v1->y, v2->y),
		.z = ft_fmin(v1->z, v2->z)});
}

__attribute__((always_inline))
t_vec3d	v3d_max(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){
		.x = ft_fmax(v1->x, v2->x),
		.y = ft_fmax(v1->y, v2->y),
		.z = ft_fmax(v1->z, v2->z)});
}

__attribute__((always_inline))
t_vec3d	v3d_opp(const t_vec3d *v1)
{
	return ((t_vec3d){.v = -v1->v});
}

__attribute__((always_inline))
t_vec3d	v3d_abs(const t_vec3d *v)
{
	return ((t_vec3d){
		.x = ft_fabs(v->x),
		.y = ft_fabs(v->y),
		.z = ft_fabs(v->z)});
}
