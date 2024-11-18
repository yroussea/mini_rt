/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_checkerboard.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:20:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:34:44 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer/option.h>
#include <math.h>
#include <stdbool.h>

bool	rt_backend_raytracer_checkerboard(double a, double b)
{
	const int	x = fabs(floor(a / RT_CHECKER_SIZE));
	const int	y = fabs(floor(b / RT_CHECKER_SIZE));

	return ((x % 2) ^ (y % 2));
}
