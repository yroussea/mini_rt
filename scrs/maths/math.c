/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/28 07:15:47 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

t_v4f cross(t_v4f v1, t_v4f v2)
{
    t_v4f result;
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
}

float	det2d(t_v4f abcd)
{
	return (abcd[0] * abcd[3] - abcd[1] * abcd[2]);
}

t_v4f	cramer_rule_2d(t_v4f ab, t_v4f c_)
{
	t_v4f	x_;
	float	bot_det = det2d(ab);

	x_[0] = det2d((t_v4f){c_[0], c_[1], ab[2], ab[3]}) / bot_det;
	x_[1] = det2d((t_v4f){ab[0], ab[1], c_[0], c_[1]}) / bot_det;
	return x_;
}

float	dot_product(t_v4f v1)
{
	return (v1[0] + v1[1] + v1[2]);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	norm(t_v4f vector)
{
	return (pow(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2), 0.5));
}

t_v4f	normalize(t_v4f vector)
{
	return (vector / norm(vector));
}

t_v4f	mult_vector(t_v4f a, t_v4f b)
{
	return (t_v4f){a[0] * b[0], a[1] * b[1], a[2] * b[2], 0};
}
float	sign(float x)
{
	if (x >= 0)
		return (1);
	return (-1);
}

int	vec_to_rgb(t_v4f v)
{
	int		r = 255*min(max(0,v[0]), 1);
	int		g = 255*min(max(0,v[1]), 1);
	int		b = 255*min(max(0,v[2]), 1);
	return (0xFF000000 + (r << 16) + (g << 8) + b);
}


