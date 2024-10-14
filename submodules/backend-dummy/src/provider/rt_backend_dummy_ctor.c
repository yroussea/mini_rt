/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_ctor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:15:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 07:12:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

t_rt_backend	*rt_backend_dummy_provider(t_rt *rt, size_t width,
					size_t height);

__attribute__((constructor))
void	rt_backend_dummy_ctor(void)
{
	rt_backend_provider_register((t_rt_backend_provider){
		.name = "dummy",
		.fn = rt_backend_dummy_provider
	});
}
