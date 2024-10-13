/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 21:22:50 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/print.h"
#include "mlx.h"
#include "object.h"
#include "ray.h"
#include <parsing.h>
#include <stdlib.h>
#include <mlx_manage.h>

void	clear_objs(void)
{
	t_objs	*objs;
	t_objs	*tmp;

	get_objs(&objs);
	while (objs)
	{
		tmp = objs->next;
		free(objs->obj);
		free(objs);
		objs = tmp;
	}
}
void	pixelisation_big(void *var)
{
	((t_mdata *)var)->pixelisation = next_size(WIDTH, HEIGHT, ((t_mdata *)var)->pixelisation, 1);
}
void	pixelisation_small(void *var)
{
	((t_mdata *)var)->pixelisation = next_size(WIDTH, HEIGHT, ((t_mdata *)var)->pixelisation, 0);
}
void	pixelisation_reset(void *var)
{
	((t_mdata *)var)->pixelisation = 1;
}

int	main(int ac, char **av)
{
	t_mdata	mdata;

	if (!ac)
		return (1);
	parsing(av[1]);

	mm_init(&mdata, clear_objs, gen_image, (t_loop_param){ray_launching, lauch_one_ray});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, ESCAPE, mm_kill});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, PLUS_KEY, pixelisation_big});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, MINUS_KEY, pixelisation_small});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, LEFT_ENTER_KEY, pixelisation_reset});
	mm_loop(&mdata);
	mm_kill(&mdata);
}

