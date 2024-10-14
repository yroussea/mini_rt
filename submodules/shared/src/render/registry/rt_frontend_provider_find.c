/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_provider_find.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:30:06 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:42:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/render/frontend.h>

t_rt_frontend_provider	*rt_frontend_provider_find(const char *name)
{
	t_rt_frontend_provider	*provider;
	size_t					i;

	i = 0;
	while (i < RT_FRONTEND_PROVIDERS_MAX)
	{
		provider = rt_frontend_providers() + i;
		if (ft_strcmp(provider->name, name) == 0)
			return (provider);
		i++;
	}
	return (NULL);
}
