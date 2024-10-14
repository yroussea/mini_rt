/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_provider_register.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:21:59 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:49:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/log.h>
#include <rt/render/frontend.h>

void	rt_frontend_provider_register(t_rt_frontend_provider provider)
{
	t_rt_frontend_provider	*frontend_providers;
	size_t					i;

	i = 0;
	frontend_providers = rt_frontend_providers();
	while (frontend_providers[i].name)
	{
		if (!ft_strcmp(frontend_providers[i].name, provider.name))
			return ;
		i++;
	}
	RT_DEBUG("registering %s\n", provider.name);
	frontend_providers[i] = provider;
}
