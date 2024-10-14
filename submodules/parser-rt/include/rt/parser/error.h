/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:45:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/12 02:45:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# undef ERROR_H
# ifndef __RT_PARSER_ERROR_H__
#  define __RT_PARSER_ERROR_H__

/**
 * @file error.h
 * @brief Error management system for libparser.rt
 * @see `struct s_rt_parser_error`
 */

#  include <stddef.h>

// Shadow declaration, see <rt/parser.h>
typedef struct s_rt_parser				t_rt_parser;

/**
 * @brief Sub error types for `PARSER_ERR_FILE`.
 * @see `struct s_rt_parser_file_context`
 */
enum	e_rt_parser_file_error
{
	FILE_ERR_UNKNOWN_ID = 0,
	FILE_ERR_MISSING_ID,
	FILE_ERR_INVALID_CHAR,
	FILE_ERR_INVALID_NUMBER,
	FILE_ERR_MISSING_PART,
	FILE_ERR_NON_EMPTY_LINE,
	FILE_ERR_WRONG_ORDER,
};

/**
 * @brief Context information specific to the `PARSER_ERR_FILE` error type;
 *		  allows for clean and descriptive error messages.
 */
typedef struct s_rt_parser_file_context
{
	enum e_rt_parser_file_error	type;
	const char					*filename;
	size_t						line;
	size_t						column;
	size_t						length;
	const char					*error_message;
	const char					*possible_fix;
}	t_rt_parser_file_context;

/**
 * @brief An enum of the possible error types.
 */
enum	e_rt_parse_error
{
	PARSE_ERR_OK = 0,
	PARSE_ERR_ALLOC,
	PARSE_ERR_SYSCALL,
	PARSE_ERR_FILE,
	PARSE_ERR_UNKNOWN,
	_PARSE_ERR_SIZE,
};

typedef struct s_rt_parse_error
{
	enum e_rt_parse_error	type;
	union
	{
		void						*data;
		t_rt_parser_file_context	file_context;
	};
}	t_rt_parse_error;

t_rt_parse_error	rt_parse_ok(void);
t_rt_parse_error	rt_parse_err(enum e_rt_parse_error type);
t_rt_parse_error	rt_parse_errd(enum e_rt_parse_error type, void *data);
t_rt_parse_error	rt_parse_errs(enum e_rt_parse_error type,
						const char *string_data);
t_rt_parse_error	rt_parse_err_file(t_rt_parser_file_context context);

const char			*rt_parse_err_str(enum e_rt_parse_error err);
void				rt_parse_err_print(t_rt_parser *parser,
						t_rt_parse_error err);

# endif // __RT_PARSER_ERROR_H__
#endif // ERROR_H
