/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_dtor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:14:44 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/15 00:18:58 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/devreload.h>

__attribute__((destructor))
void	rt_devrl_dtor(void)
{
	t_rt_backend_provider	*backend;
	t_rt_frontend_provider	*frontend;

	RT_DEBUG("devreload dtor\n");
	backend = rt_backend_providers();
	while (backend[0].name)
	{
		ft_strdel((char **)&backend[0].name);
		backend++;
	}
	frontend = rt_frontend_providers();
	while (frontend[0].name)
	{
		ft_strdel((char **)&frontend[0].name);
		frontend++;
	}
}
