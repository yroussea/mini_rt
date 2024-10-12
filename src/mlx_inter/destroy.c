/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:26:23 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/12 22:55:24 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <mlx_manage.h>
#include <stdlib.h>

void	mm_kill(void *var)
{
	t_mdata	*mdata;

	mdata = var;
	mlx_loop_end(mdata->mlx);
	mlx_destroy_image(mdata->mlx, mdata->img);
	mlx_destroy_window(mdata->mlx, mdata->wind);
	mlx_destroy_display(mdata->mlx);
	if (mdata->destroy_fnct)
		mdata->destroy_fnct();
	exit(EXIT_SUCCESS);
}
