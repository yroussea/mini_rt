/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 22:45:15 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:43:49 by kiroussa         ###   ########.fr       */
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

#  include <stdarg.h>
#  include <stdbool.h>
#  include <stddef.h>

// Shadow declaration, see <rt/parser.h>
typedef struct s_rt_parser				t_rt_parser;

/**
 * @brief Sub error types for `PARSER_ERR_FILE`.
 * @see `struct s_rt_parser_file_context`
 * @see `rt_parse_err_print.c#rt_err_file_strtype`
 */
enum	e_rt_parser_file_error
{
	FILE_ERR_UNKNOWN_ID = 0,
	FILE_ERR_INVALID_CHAR,
	FILE_ERR_INVALID_TOKEN,
	FILE_ERR_INVALID_NUMBER,
	FILE_ERR_MISSING_PART,
	FILE_ERR_TOO_MANY_PARTS,
	FILE_ERR_NON_EMPTY_LINE,
	FILE_ERR_WRONG_ORDER,
	FILE_ERR_DUPLICATE,
	_FILE_ERR_SIZE,
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
	struct s_note
	{
		size_t					line;
		size_t					column;
		size_t					length;
		const char				*message;
	}	note;
	char						*possible_fix;
}	t_rt_parser_file_context;

/**
 * @brief An enum of the possible error types.
 */
typedef enum e_rt_parse_error
{
	PARSE_ERR_OK = 0,
	PARSE_ERR_ALLOC,
	PARSE_ERR_SYSCALL,
	PARSE_ERR_FILE,
	PARSE_ERR_FILE_READ,
	PARSE_ERR_MISSING_REQUIRED,
	PARSE_ERR_BAD_USAGE,
	PARSE_ERR_NULL,
	PARSE_ERR_UNKNOWN,
	_PARSE_ERR_SIZE,
}	t_rt_parse_error_type;

typedef struct s_rt_parse_error
{
	enum e_rt_parse_error	type;
	union
	{
		void						*data;
		t_rt_parser_file_context	file_context;
	};
}	t_rt_parse_error;

bool				rt_parse_is_ok(t_rt_parse_error err);
bool				rt_parse_is_err(t_rt_parse_error err);

t_rt_parse_error	rt_parse_ok(void);
t_rt_parse_error	rt_parse_okd(void *data);
t_rt_parse_error	rt_parse_err(enum e_rt_parse_error type);
t_rt_parse_error	rt_parse_errd(enum e_rt_parse_error type, void *data);
t_rt_parse_error	rt_parse_errs(enum e_rt_parse_error type,
						const char *string_data, ...);
t_rt_parse_error	rt_parse_err_file(t_rt_parser_file_context context);

const char			*rt_parse_err_str(enum e_rt_parse_error err);
void				rt_parse_err_print(t_rt_parser *parser,
						t_rt_parse_error err);

#  ifndef __ERROR_SPEC__
#   define __ERROR_SPEC__

// This defines a "result" type, as well as common function related to it.

//  errspec:base
#   define RESULT	t_rt_parse_error
#   define RES_OK	rt_parse_is_ok
#   define RES_ERR	rt_parse_is_err

#   define OK		rt_parse_ok
#   define OKD		rt_parse_okd
#   define ERR		rt_parse_err
#   define ERRD		rt_parse_errd
#   define ERRS		rt_parse_errs
//  errspec:ext-ignore
#   define ERR_FILE	rt_parse_err_file

#   define ERROR_TYPE	t_rt_parse_error_type
#   define ERROR_STR	rt_parse_err_str
#   define ERROR_PRINT	rt_parse_err_print
//  errspec:end

#  endif

# endif // __RT_PARSER_ERROR_H__
#endif // ERROR_H
