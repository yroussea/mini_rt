/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parser_rt_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:25:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:53:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/parser.h>

static void	rt_parser_object_init(t_rt_object_parser *objp, const char *id,
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

t_rt_object_parser	rt_dummy_object(void)
{
	t_rt_object_parser	obj;

	rt_parser_object_init(&obj, "BB", "sphere", 0);
	obj.sequence_size = 1;
	obj.required = 1;
	return (obj);
}

t_rt_object_parser	rt_dummy_object2(void)
{
	t_rt_object_parser	obj;

	rt_parser_object_init(&obj, "CC", "cylinder", 16);
	obj.sequence_size = 3;
	obj.required = 2;
	return (obj);
}

RESULT	rt_cli_parser_rt_init(t_rt_parser *parser)
{
	RESULT	res;

	res = rt_parser_object_register(parser, rt_dummy_object());
	if (RES_OK(res))
		res = rt_parser_object_register(parser, rt_dummy_object2());
	return (res);
}
