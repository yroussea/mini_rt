/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_ctor.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 03:15:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:50:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>

__attribute__((constructor))
void	rt_backend_raytracer_ctor(void)
{
	rt_backend_provider_register((t_rt_backend_provider){
		.name = "raytracer",
		.fn = rt_backend_raytracer_provider
	});
}
