/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:38:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/11 23:22:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/colors.h>
#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <rt/log.h>
#include <rt/parser.h>
#include <unistd.h>

#define OUT STDERR_FILENO
#define ITALIC "\033[3m"

static void	rt_parse_err_file_print_column(const t_rt_parser *parser,
						const t_rt_parser_file_context *context)
{
	(void)parser;
	(void)context;
	printf("todo: col display\n");
}

static void	rt_parse_err_file_print_extras(const t_rt_parser *parser,
						const t_rt_parser_file_context *context)
{
	(void)parser;
	if (context->possible_fix)
		ft_dprintf(OUT, B_GREEN"help"RESET""GREEN": "RESET"%s\n",
			context->possible_fix);
}

static const char	*rt_err_file_strtype(enum e_rt_parser_file_error type)
{
	static const char	*err_file_strtype[] = {
	[FILE_ERR_UNKNOWN_ID] = "unknown object identifier",
	[FILE_ERR_INVALID_CHAR] = "invalid character",
	[FILE_ERR_INVALID_NUMBER] = "invalid digit, or number too large",
	[FILE_ERR_MISSING_PART] = "missing part of the object",
	[FILE_ERR_NON_EMPTY_LINE] = "empty lines should not contain spaces",
	[FILE_ERR_WRONG_ORDER] = "object properties specified in the wrong order",
	};

	if (type >= _FILE_ERR_SIZE || type < 0)
		return ("unknown file error");
	return (err_file_strtype[type]);
}

static void	rt_parse_err_file_print(const t_rt_parser *parser,
						const t_rt_parser_file_context *context)
{
	const t_rt	*rt = parser->rt;
	size_t		spacing;

	spacing = ft_ulllen(context->line);
	rt_error(rt, B_RED"error"RESET":"BOLD" %s\n"RESET,
		rt_err_file_strtype(context->type));
	ft_dprintf(OUT, "%*s"BLUE"-->"RESET" %s\n"RESET, spacing, "",
		context->filename);
	if ((int)context->line != -1)
	{
		ft_dprintf(OUT, BLUE "%*s | \n" RESET, spacing, "");
		ft_dprintf(OUT, BLUE "%*d | "RESET"%s\n", spacing, (int)context->line,
			parser->buffer[context->line - 1]);
		if ((int)context->column != -1)
		{
			rt_parse_err_file_print_column(parser, context);
		}
		else
			ft_dprintf(OUT, BLUE "%*s | "RESET""B_RED"^^^ "RESET""RED
				ITALIC"(entire line) "RESET""RED"  %s\n" RESET, spacing, "",
				context->error_message);
	}
	rt_parse_err_file_print_extras(parser, context);
}

void	rt_parse_err_print(t_rt_parser *parser, t_rt_parse_error err)
{
	const t_rt	*rt = parser->rt;
	const char	*err_type = ERROR_STR(err.type);

	if (err_type == NULL)
		return ;
	if (err.type == PARSE_ERR_FILE)
		rt_parse_err_file_print(parser, &err.file_context);
	else
	{
		rt_error(rt, B_RED"error"RESET":"BOLD" %s\n"RESET, err_type);
		if (err.data)
			ft_dprintf(OUT, BLUE" -->"RESET""RED" %s\n"RESET, err.data);
	}
	if (err.data)
		ft_strdel((char **) &err.data);
}
