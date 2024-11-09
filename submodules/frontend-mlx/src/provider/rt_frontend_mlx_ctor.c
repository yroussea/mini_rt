/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_mlx_ctor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:01:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:50:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend/macrolibx.h>

__attribute__((constructor))
static void	rt_frontend_mlx_ctor(void)
{
	rt_frontend_provider_register((t_rt_frontend_provider){
		.name = "mlx",
		.fn = rt_frontend_mlx_provider
	});
}
