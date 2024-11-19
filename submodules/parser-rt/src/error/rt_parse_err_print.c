/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:38:24 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:26:42 by kiroussa         ###   ########.fr       */
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

static void	rt_parse_err_file_print_column(
	size_t col,
	size_t len,
	size_t spacing,
	const char *msg
) {
	char	*under;
	size_t	i;

	under = ft_calloc(len + 1, sizeof(char));
	if (!under)
	{
		ft_dprintf(OUT, BLUE"%*s | %*s"RESET""B_RED, spacing, "",
			col, "");
		i = 0;
		while (i++ < len)
			ft_putchar_fd(OUT, '^');
		ft_dprintf(OUT, RESET" "RED"%s\n"RESET, msg);
	}
	else
	{
		ft_memset(under, '^', len);
		ft_dprintf(OUT, BLUE"%*s | %*s"RESET""B_RED"%s "RESET""RED"%s\n"RESET,
			spacing, "", col, "", under, msg);
		free(under);
	}
}

static void	rt_parse_err_file_print_extras(const t_rt_parser *parser,
				const t_rt_parser_file_context *context)
{
	size_t		spacing;

	if (context->note.message && (int)context->note.line != -1)
	{
		ft_dprintf(OUT, B_BLUE"note"RESET""BLUE":"RESET"\n");
		spacing = ft_ulllen(context->note.line);
		ft_dprintf(OUT, BLUE "%*s | \n" RESET, spacing, "");
		ft_dprintf(OUT, BLUE "%*d | "RESET"%s\n", spacing,
			(int)context->note.line, parser->buffer[context->note.line - 1]);
		rt_parse_err_file_print_column(context->note.column,
			context->note.length, spacing, context->note.message);
	}
	if (context->possible_fix)
		ft_dprintf(OUT, B_GREEN"help"RESET""GREEN": "RESET"%s\n",
			context->possible_fix);
}

const char	*rt_err_file_strtype(enum e_rt_parser_file_error type)
{
	static const char	*err_file_strtype[] = {
	[FILE_ERR_UNKNOWN_ID] = "unknown object identifier",
	[FILE_ERR_INVALID_CHAR] = "encountered an invalid character",
	[FILE_ERR_INVALID_TOKEN] = "an invalid token was provided",
	[FILE_ERR_INVALID_NUMBER] = "number provided is invalid",
	[FILE_ERR_MISSING_PART] = "missing part of the object",
	[FILE_ERR_TOO_MANY_PARTS] = "too many parameters provided",
	[FILE_ERR_NON_EMPTY_LINE] = "empty lines should not contain spaces",
	[FILE_ERR_WRONG_ORDER] = "object properties specified in the wrong order",
	[FILE_ERR_DUPLICATE] = "unique object is already defined in the scene",
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
	ft_putchar_fd(OUT, '\n');
	rt_error(rt, B_RED"error"RESET":"BOLD" %s\n"RESET,
		rt_err_file_strtype(context->type));
	ft_dprintf(OUT, "%*s"BLUE"-->"RESET" %s\n"RESET, spacing, "",
		context->filename);
	if ((int)context->line >= 0)
	{
		ft_dprintf(OUT, BLUE "%*s | \n" RESET, spacing, "");
		ft_dprintf(OUT, BLUE "%*d | "RESET"%s\n", spacing, (int)context->line,
			parser->buffer[context->line - 1]);
		if ((int)context->column >= 0)
			rt_parse_err_file_print_column(context->column, context->length,
				spacing, context->error_message);
		else
			ft_dprintf(OUT, BLUE "%*s | "RESET""B_RED"^^^ "RESET""RED
				ITALIC"(entire line) "RESET""RED"  %s\n" RESET, spacing, "",
				context->error_message);
	}
	rt_parse_err_file_print_extras(parser, context);
	ft_putchar_fd(OUT, '\n');
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
	rt_parse_err_free(parser, err);
}
