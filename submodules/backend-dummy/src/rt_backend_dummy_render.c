/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_render.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:56:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/26 22:08:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>

t_color	*rt_backend_dummy_render(t_rt_backend *backend)
{
	return ((t_color *) backend->data);
}
