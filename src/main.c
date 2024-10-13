/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:31:26 by yroussea         ###   ########.fr       */
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
void	pixelisation(void *var)
{
	((t_mdata *)var)->pixelisation += 1;
}

int	main(int ac, char **av)
{
	t_mdata	mdata;

	if (!ac)
		return (1);
	parsing(av[1]);

	mm_init(&mdata, clear_objs, gen_image, (t_loop_param){ray_launching, lauch_one_ray});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, ESCAPE, mm_kill});
	mm_add_event(&mdata, (t_event){MLX_KEYUP, A_KEY, pixelisation});
	mm_loop(&mdata);
	mm_kill(&mdata);
}

