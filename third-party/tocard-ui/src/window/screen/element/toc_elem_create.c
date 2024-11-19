/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_elem_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:10:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 19:36:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>
#include <stdlib.h>

t_toc_elem	*toc_elem_create(int id, t_toc_elem_def definition)
{
	const t_toc_elem	base = (t_toc_elem){
		.screen = NULL, .def = definition, .id = id,
		.x = 0, .y = 0, .width = 0, .height = 0,
		.last_click = false, .enabled = true, .visible = true,
		.focused = false
	};
	t_toc_elem			*elem;

	elem = malloc(sizeof(t_toc_elem));
	if (!elem)
		return (NULL);
	*elem = base;
	return (elem);
}
