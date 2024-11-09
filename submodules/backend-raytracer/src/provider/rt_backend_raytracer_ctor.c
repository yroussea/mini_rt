/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ctor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:15:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/07 00:39:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/log.h>
#include <rt/render/backend/raytracer.h>

__attribute__((constructor))
void	rt_backend_raytracer_ctor(void)
{
	RT_DEBUG("WHAT THE FUCK\n");
	rt_backend_provider_register((t_rt_backend_provider){
		.name = "raytracer",
		.fn = rt_backend_raytracer_provider
	});
}
