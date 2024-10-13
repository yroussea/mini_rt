/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:32:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 14:09:52 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <mlx_manage.h>

int	mm_loop_hook(void *var)
{
	t_mdata	*mdata;

	mdata = var;
	if (mdata->loop_fnct)
		mdata->loop_fnct(mdata);
	return (1);
}

void	mm_loop(void *var)
{
	t_mdata	*mdata;

	mdata = var;
	mm_event(mdata);
	mlx_loop_hook(mdata->mlx, mm_loop_hook, mdata);
	mlx_loop(mdata->mlx);
}
