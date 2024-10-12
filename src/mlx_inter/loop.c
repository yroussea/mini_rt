/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:32:07 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/12 22:08:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <mlx_manage.h>

void	mm_loop(void *var)
{
	t_mdata	*mdata;

	mdata = var;
	mm_event(mdata);
	if (mdata->loop_fnct)
		mdata->loop_fnct(mdata);
	mlx_loop(mdata->mlx);
}
