/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 01:26:34 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:27:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <rt/parser.h>

void	rt_parse_err_free(t_rt_parser *parser, t_rt_parse_error err)
{
	(void)parser;
	if (err.data && err.type != PARSE_ERR_FILE)
		ft_strdel((char **) &err.data);
	else if (err.type == PARSE_ERR_FILE
		&& (err.file_context.type == FILE_ERR_UNKNOWN_ID
			|| err.file_context.type == FILE_ERR_TOO_MANY_PARTS))
		ft_strdel((char **) &err.file_context.possible_fix);
	else if (err.type == PARSE_ERR_FILE
		&& err.file_context.type == FILE_ERR_MISSING_PART)
		ft_strdel((char **) &err.file_context.error_message);
}
