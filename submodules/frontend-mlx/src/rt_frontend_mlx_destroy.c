/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 05:27:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 07:55:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend/macrolibx.h>

void	rt_frontend_mlx_destroy(t_rt_frontend *self)
{
	t_rt_frontend_mlx	*data;

	data = (t_rt_frontend_mlx *)self->data;
	if (!data)
		return ;
	if (data->engine)
		toc_engine_destroy(data->engine);
	free(data);
	self->data = NULL;
}
