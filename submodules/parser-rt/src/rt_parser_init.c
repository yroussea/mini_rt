/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:39:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/31 08:21:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser.h>

RESULT	rt_parser_init(t_rt_parser *parser, const t_rt *rt)
{
	ft_memset(parser, 0, sizeof(t_rt_parser));
	parser->rt = rt;
	return (OK());
}
