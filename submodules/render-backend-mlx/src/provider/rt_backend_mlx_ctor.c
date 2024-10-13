/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_mlx_ctor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:01:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 01:03:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/render/backend.h>

t_rt_render_backend	*rt_backend_mlx_provider(t_rt *rt);

__attribute__((constructor))
static void	rt_backend_mlx_ctor(void)
{
	size_t	i;

	i = 0;
	while (g_backend_providers[i].name)
	{
		if (!ft_strcmp(g_backend_providers[i].name, "mlx"))
			return ;
		i++;
	}
	g_backend_providers[i].name = "mlx";
	g_backend_providers[i].fn = rt_backend_mlx_provider;
}
