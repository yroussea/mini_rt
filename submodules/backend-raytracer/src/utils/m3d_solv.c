/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m3d_solv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 01:31:51 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/09 01:28:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/math/vector.h>
#include <ft/math/matrix.h>

double	m3d_det(t_mat3d x)
{
	double	res;

	res = x.m[0][0] * x.m[1][1] * x.m[2][2];
	res += x.m[0][1] * x.m[1][2] * x.m[2][0];
	res += x.m[0][2] * x.m[1][0] * x.m[2][1];
	res -= x.m[0][0] * x.m[1][2] * x.m[2][1];
	res -= x.m[0][1] * x.m[1][0] * x.m[2][2];
	res -= x.m[0][2] * x.m[1][1] * x.m[2][0];
	return (res);
}

t_mat3d	m3d_inv(t_mat3d x)
{
	const double	det = m3d_det(x);
	t_mat3d			res;

	res.m[0][0] = (x.m[1][1] * x.m[2][2] - x.m[1][2] * x.m[2][1]) / det;
	res.m[0][1] = (x.m[0][2] * x.m[2][1] - x.m[0][1] * x.m[2][2]) / det;
	res.m[0][2] = (x.m[0][1] * x.m[1][2] - x.m[0][2] * x.m[1][1]) / det;
	res.m[1][0] = (x.m[1][2] * x.m[2][0] - x.m[1][0] * x.m[2][2]) / det;
	res.m[1][1] = (x.m[0][0] * x.m[2][2] - x.m[0][2] * x.m[2][0]) / det;
	res.m[1][2] = (x.m[0][2] * x.m[1][0] - x.m[0][0] * x.m[1][2]) / det;
	res.m[2][0] = (x.m[1][0] * x.m[2][1] - x.m[1][1] * x.m[2][0]) / det;
	res.m[2][1] = (x.m[0][1] * x.m[2][0] - x.m[0][0] * x.m[2][1]) / det;
	res.m[2][2] = (x.m[0][0] * x.m[1][1] - x.m[0][1] * x.m[1][0]) / det;
	return (res);
}

static t_vec3d	m3d_v3d_mult(t_mat3d a, t_vec3d b)
{
	t_vec3d	res;

	res.x = a.m[0][0] * b.x + a.m[0][1] * b.y + a.m[0][2] * b.z;
	res.y = a.m[1][0] * b.x + a.m[1][1] * b.y + a.m[1][2] * b.z;
	res.z = a.m[2][0] * b.x + a.m[2][1] * b.y + a.m[2][2] * b.z;
	return (res);
}

t_mat3d	m3d(t_vec3d col1, t_vec3d col2, t_vec3d col3)
{
	t_mat3d			res;

	res.m[0][0] = col1.x;
	res.m[0][1] = col2.x;
	res.m[0][2] = col3.x;
	res.m[1][0] = col1.y;
	res.m[1][1] = col2.y;
	res.m[1][2] = col3.y;
	res.m[2][0] = col1.z;
	res.m[2][1] = col2.z;
	res.m[2][2] = col3.z;
	return (res);
}

t_vec3d	m3d_solv(t_mat3d a, t_vec3d b)
{
	const t_mat3d	inv = m3d_inv(a);

	return (m3d_v3d_mult(inv, b));
}
