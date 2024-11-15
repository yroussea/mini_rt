/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:11:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 07:13:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <stdbool.h>
#include <rt/parser.h>

void	rt_parser_object_init(t_rt_object_parser *objp, const char *id,
			int enum_id, size_t size)
{
	size_t		i;
	const char	*name;

	ft_memset(objp, 0, sizeof(t_rt_object_parser));
	objp->id = id;
	objp->enum_id = enum_id;
	objp->size = size;
	if (objp->parser && objp->parser->name_fn)
	{
		name = objp->parser->name_fn(objp->enum_id);
		i = 0;
		while (name && name[i])
		{
			if (!ft_isupper(name[i]))
				return ;
			i++;
		}
		objp->is_unique = true;
	}
}
