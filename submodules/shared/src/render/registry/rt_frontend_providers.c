/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_providers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:31:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:31:27 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend.h>

t_rt_frontend_provider	*rt_frontend_providers(void)
{
	static t_rt_frontend_provider	frontend_providers
	[RT_FRONTEND_PROVIDERS_MAX]
		= {0};

	return (frontend_providers);
}
