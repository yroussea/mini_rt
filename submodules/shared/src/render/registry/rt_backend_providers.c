/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_providers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:05:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:31:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

t_rt_backend_provider	*rt_backend_providers(void)
{
	static t_rt_backend_provider	backend_providers
	[RT_BACKEND_PROVIDERS_MAX]
		= {0};

	return (backend_providers);
}
