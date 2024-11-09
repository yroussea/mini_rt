/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_handoff.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 05:28:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 05:52:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend/macrolibx.h>

void	rt_frontend_mlx_handoff(t_rt_frontend *self)
{
	const t_rt_frontend_mlx	*frontend = (t_rt_frontend_mlx *)self->data;

	toc_engine_await(frontend->engine);
}
