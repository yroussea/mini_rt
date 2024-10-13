#include "ft/math/vector.h"
#include "mlx.h"
#include "object.h"
#include <ray.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx_manage.h>
#include <sys/types.h>
// #include <rt.h>
// #include <maths.h>


void	lauch_one_ray(t_objs *objs, t_ray ray, int x, int y)
{
	(void)ray;
	(void)x;
	(void)y;
	(void)objs;
	//transphorming ray
	//find hit
	//	get_shade
	mm_draw_pixel(x, (t_vec3d){0,1,0});
}

void	ray_launching(t_objs *obj, void one_ray(t_objs *, t_ray , int , int ),
	ushort w_size, ushort h_size)
{
	t_ray	ray;
	ushort	x;
	ushort	y;

	ray.center = ((t_camera *)obj->obj)->point;
	y = 0;
	while (y < h_size)
	{
		x = 0;
		while (x < w_size)
		{
			one_ray(obj, ray, x, y);
			x++;
		}
		mm_draw_ligne(y);
		y++;
	}
}

void	gen_image(t_mdata *m_data)
{
	static t_objs	*all_objs = NULL;

	printf("%s\n", __func__);
	if (!all_objs)
		get_objs(&all_objs);
	m_data->param_fnct.all_ray(all_objs, m_data->param_fnct.one_ray,
		WIDTH / m_data->pixelisation, HEIGHT / m_data->pixelisation);
	mm_draw_image(m_data);
}


