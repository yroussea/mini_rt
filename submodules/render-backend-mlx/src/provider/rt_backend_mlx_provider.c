/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_mlx_provider.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:02:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 01:02:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

t_rt_render_backend	*rt_backend_mlx_provider(t_rt *rt)
{
	static t_rt_render_backend	backend;

	backend.name = "mlx";
	backend.init = NULL;
	backend.destroy = NULL;
	backend.render = NULL;
	return (&backend);
}
