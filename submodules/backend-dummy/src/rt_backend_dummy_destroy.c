/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_backend_dummy_destroy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 06:55:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 07:16:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/backend.h>
#include <stdlib.h>

void	rt_backend_dummy_destroy(t_rt_backend *backend)
{
	if (backend->data)
		free(backend->data);
	backend->data = NULL;
}
