/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:38:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:55:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/log.h>
#include <rt/parser.h>

__attribute__((unused))
static void	rt_parse_err_file_print(const t_rt_parser *parser,
						const t_rt_parser_file_context *context)
{
	const t_rt	*rt = parser->rt;

	(void)context;
	rt_error(rt, "parser: file format error\n");
}

static void	rt_parse_err_free(t_rt_parser *parser, t_rt_parse_error err)
{
	(void)parser;
	if (err.type == PARSE_ERR_FILE_READ)
		ft_strdel((char **) &err.data);
}

void	rt_parse_err_print(t_rt_parser *parser, t_rt_parse_error err)
{
	const t_rt	*rt = parser->rt;
	const char	*err_type = ERROR_STR(err.type);

	if (err_type == NULL)
		return ;
	// if (err.type == PARSE_ERR_FILE)
	// 	rt_parse_err_file_print(parser, &err.file_context);
	else
	{
		if (err.data)
			rt_error(rt, "parser: %s\n", (char *)err.data);
		else
			rt_error(rt, "parser: %s\n", err_type);
	}
	rt_parse_err_free(parser, err);
}
