/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_checkerboard.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:20:44 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/03 13:41:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CHECKER_SIZE 25
#include <math.h>
#include <stdbool.h>

bool	rt_backend_raytracer_checkerboard(double a, double b)
{
	const int x = fabs(floor(a / CHECKER_SIZE));
	const int y = fabs(floor(b / CHECKER_SIZE));

	return ((x % 2) ^ (y % 2));
}
