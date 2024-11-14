/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 07:11:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:12:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <stdbool.h>
#include <rt/parser.h>

void	rt_parser_object_init(t_rt_object_parser *objp, const char *id,
			const char *name, size_t size)
{
	size_t	i;

	ft_memset(objp, 0, sizeof(t_rt_object_parser));
	objp->id = id;
	objp->name = name;
	objp->size = size;
	i = 0;
	while (name && name[i])
	{
		if (!ft_isupper(name[i]))
			return ;
		i++;
	}
	objp->is_unique = true;
}
