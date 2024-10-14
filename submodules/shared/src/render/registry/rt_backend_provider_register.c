/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_provider_register.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:21:31 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:49:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/log.h>
#include <rt/render/backend.h>

void	rt_backend_provider_register(t_rt_backend_provider provider)
{
	t_rt_backend_provider	*backend_providers;
	size_t					i;

	i = 0;
	backend_providers = rt_backend_providers();
	while (backend_providers[i].name)
	{
		if (!ft_strcmp(backend_providers[i].name, provider.name))
			return ;
		i++;
	}
	RT_DEBUG("registering %s\n", provider.name);
	backend_providers[i] = provider;
}
