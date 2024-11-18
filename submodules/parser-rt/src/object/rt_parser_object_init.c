/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:11:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:38:21 by yroussea         ###   ########.fr       */
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

	objp->id = id;
	objp->enum_id = enum_id;
	objp->size = size;
	i = 0;
	while (objp->id[i])
	{
		if (!ft_isupper(objp->id[i]))
			return ;
		i++;
	}
	objp->is_unique = true;
}
