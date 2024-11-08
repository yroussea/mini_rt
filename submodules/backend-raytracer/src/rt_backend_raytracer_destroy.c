/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_destroy.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:55:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 16:33:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <stdint.h>
#include <stdlib.h>

void	rt_backend_raytracer_destroy(t_rt_backend *backend)
{
	t_rt_backend_raytracer	*data;

	data = (t_rt_backend_raytracer *)backend->data;
	if (data)
	{
		if (data->buffer)
			free(data->buffer);
		if (data->rays)
			free((void *)(((uintptr_t)data->rays)
					- data->rays_alignment_offset));
		free(data);
		backend->data = NULL;
	}
}
