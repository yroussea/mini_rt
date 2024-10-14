/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:51:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:46:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend/raytracer.h>

int	rt_backend_raytracer_init(t_rt_backend *self)
{
	t_rt_backend_raytracer	*data;

	data = ft_calloc(1, sizeof(t_rt_backend_raytracer));
	if (!data)
		return (1);
	self->data = data;
	return (0);
}
