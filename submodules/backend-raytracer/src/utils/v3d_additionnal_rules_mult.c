/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_additionnal_rules_mult.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:37:33 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/13 13:38:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math/vector.h>

__attribute__((always_inline))
t_vec3d	v3d_mult_v3d(const t_vec3d *v1, const t_vec3d *v2)
{
	return ((t_vec3d){.v = v1->v * v2->v});
}

__attribute__((always_inline))
t_vec3d	v3d_inv(const t_vec3d *v)
{
	return ((t_vec3d){.v = 1 / v->v});
}
