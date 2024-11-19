/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 01:51:08 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 04:07:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <stdlib.h>

void	rt_parser_destroy(t_rt_parser *parser)
{
	if (parser == NULL)
		return ;
	if (parser->buffer)
		free(parser->buffer);
	parser->buffer = NULL;
	if (parser->read_buffer)
		free(parser->read_buffer);
	parser->read_buffer = NULL;
	parser->nlines = 0;
	ft_lst_free(&parser->result, NULL);
}
