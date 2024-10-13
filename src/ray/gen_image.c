/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:59:19 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 16:31:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft/math/vector.h"
// #include "mlx.h"
// #include "object.h"
// #include <sys/types.h>
#include "object.h"
#include <ray.h>
#include <mlx_manage.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>

void	lauch_one_ray(t_objs *objs, t_ray ray, int x)
{
	t_objs	*objs_hit;
	(void)ray;
	(void)x;
	(void)objs;
	//find hit
	//	get_shade
	objs_hit = NULL;
	if (find_hit(&ray, objs, &objs_hit) != INFINITY)
		mm_draw_pixel(x, objs_hit->colors);
	else
		mm_draw_pixel(x, (t_vec3d){0, 0, 1});
}

void	ray_launching(t_mdata *mdata, void one_ray(t_objs *, t_ray, int),
	ushort w_size, ushort h_size)
{
	static t_objs	*all_objs = NULL;
	t_camera		*cam;
	t_ray			ray;
	ushort			x;
	ushort			y;

	if (!all_objs)
		get_objs(&all_objs);
	cam = all_objs->obj;
	ray.center = cam->point;
	y = 0;
	while (y < h_size)
	{
		x = 0;
		while (x < w_size)
		{
			eye_rays(&ray, get_width((float)x, cam->fov), get_height((float)y));
			one_ray(all_objs->next, ray, x / mdata->pixelisation);
			x += mdata->pixelisation;
		}
		mm_draw_ligne(y);
		y += mdata->pixelisation;
	}
}

void	gen_image(t_mdata *m_data)
{
	m_data->param_fnct.all_ray(m_data, m_data->param_fnct.one_ray,
		WIDTH, HEIGHT);
	mm_draw_image(m_data);
}
