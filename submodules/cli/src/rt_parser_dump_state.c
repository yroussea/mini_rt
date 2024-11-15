/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_dump_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:26:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 07:08:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/data/list.h>
#include <rt/log.h>
#include <rt/objects.h>
#include <rt/parser.h>

const char	*rt_object_strtype(const t_rt_obj_type type)
{
	static const char	*types[] = {
	[OBJ_CAMERA] = "camera",
	[OBJ_AMBIANT_LIGHT] = "ambiant light",
	[OBJ_LIGHT] = "point light",
	[OBJ_SPHERE] = "sphere",
	[OBJ_PLANE] = "plane",
	[OBJ_CYLINDER] = "cylinder",
	[OBJ_CONE] = "cone",
	};

	if (type >= _OBJ_SIZE || type < 0)
		return ("unknown");
	return (types[type]);
}

void	rt_parser_dump_state(const t_rt *rt, t_rt_parser *parser)
{
	t_list	*result;
	t_obj	*obj;

	rt_trace(rt, "dumping parser state\n");
	rt_debug(rt, "result list size: %d\n", (int)ft_lst_size(parser->result));
	result = parser->result;
	while (result)
	{
		obj = (t_obj *)result->content;
		rt_debug(rt, "object type: %s\n", rt_object_strtype(obj->type));
		result = result->next;
	}
}
