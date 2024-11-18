/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_pixelisation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:20:33 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/18 18:10:34 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>
#include <rt/render/frontend.h>

static int	bigger_common_dividor(int w, int h, int actual)
{
	int	n;

	n = actual + 1;
	while (!((h % n == 0) && (w % n == 0)))
	{
		n++;
		if (n > h || n > w)
			return (actual);
	}
	return (n);
}

static int	smaller_common_dividor(int w, int h, int actual)
{
	int	n;

	n = actual - 1;
	while (n > 1 && !((h % n == 0) && (w % n == 0)))
		n--;
	if (n < 2)
		return (1);
	return (n);
}

static void	calcul_pixelisation(size_t x, int scale, size_t *res)
{
	*res = x / scale;
}

void	rt_pixelisation_lower(t_rt *rt)
{
	if (rt->frontend->scale == 0)
		rt->frontend->scale = 1;
	rt->frontend->scale = smaller_common_dividor(
			rt->frontend->width, rt->frontend->height, rt->frontend->scale);
	calcul_pixelisation(
		rt->frontend->width, rt->frontend->scale, &rt->backend->width);
	calcul_pixelisation(
		rt->frontend->height, rt->frontend->scale, &rt->backend->height);
	rt_backend_reload(rt);
}

void	rt_pixelisation_upper(t_rt *rt)
{
	if (rt->frontend->scale == 0)
		rt->frontend->scale = 1;
	rt->frontend->scale = bigger_common_dividor(
			rt->frontend->width, rt->frontend->height, rt->frontend->scale);
	calcul_pixelisation(
		rt->frontend->width, rt->frontend->scale, &rt->backend->width);
	calcul_pixelisation(
		rt->frontend->height, rt->frontend->scale, &rt->backend->height);
	rt_backend_reload(rt);
}
