/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_fmod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:45:52 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 02:00:25 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	rt_fmod(double x, double y)
{
	const double	a = fmod(x, y);

	return (a + y * (a < 0));
}
