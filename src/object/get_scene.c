/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:18:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:57:13 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include <rt.h>
#include <stdlib.h>

void	get_objs(t_objs	**x)
{
	static t_objs	*objs = NULL;

	if (!x)
		return ;
	if (!objs)
		objs = add_objects(NULL);
	*x = objs;
}
