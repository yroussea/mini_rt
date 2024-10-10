/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:08:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/10 19:50:52 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <maths.h>

float	sign(float x)
{
	if (x >= 0)
		return (1);
	return (-1);
}

t_vec3d	capped_vector(t_vec3d v)
{
	return ((t_vec3d){
		ft_fmin(ft_fmax(0,v.x), 1),
		ft_fmin(ft_fmax(0,v.y), 1),
		ft_fmin(ft_fmax(0,v.z), 1)
	});
}

int	vec_to_rgb(t_vec3d v)
{
	int		r = 255*ft_fmin(ft_fmax(0,v.x), 1);
	int		g = 255*ft_fmin(ft_fmax(0,v.y), 1);
	int		b = 255*ft_fmin(ft_fmax(0,v.z), 1);
	return (0xFF000000 + (r << 16) + (g << 8) + b);
}


