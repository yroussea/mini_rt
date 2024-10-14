/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_raytracer_destroy.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:55:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:45:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend/raytracer.h>
#include <stdlib.h>

void	rt_backend_raytracer_destroy(t_rt_backend *backend)
{
	t_rt_backend_raytracer	*data;

	data = (t_rt_backend_raytracer *)backend->data;
	if (data)
	{
		free(data);
		backend->data = NULL;
	}
}
