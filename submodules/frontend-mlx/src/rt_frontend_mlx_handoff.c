/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_handoff.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 05:28:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 07:29:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend/macrolibx.h>

void	rt_frontend_mlx_handoff(t_rt_frontend *self, t_rt_frontend *prev)
{
	t_rt_frontend_mlx	*data;

	data = (t_rt_frontend_mlx *)self->data;
	if (!data)
		return ;
	(void)prev;
}
