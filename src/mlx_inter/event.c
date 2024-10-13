/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:35:38 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:54:19 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <mlx_manage.h>
#include <ft/print.h>

uint	g_event_created = 0;

void	mm_add_event(t_mdata *mdata, t_event event)
{
	if (g_event_created >= NB_EVENT)
	{
		ft_dprintf(2, "more than NB_EVENT{%d} event were created!", NB_EVENT);
		return ;
	}
	mdata->event[g_event_created++] = event;
}

int	keyup_hook(int key, void *var)
{
	t_mdata	*mdata;
	uint	x;

	ft_printf("%d\n", key);
	mdata = var;
	x = 0;
	while (x < g_event_created)
	{
		if (mdata->event[x].event_type == MLX_KEYUP && \
			key == (int)mdata->event[x].keycode)
		{
			mdata->event[x].f(var);
			return (1);
		}
		x++;
	}
	return (0);
}

void	mm_event(t_mdata *mdata)
{
	mlx_on_event(mdata->mlx, mdata->wind, MLX_KEYUP, &keyup_hook, mdata);
}
