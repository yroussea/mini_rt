/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:39:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:47:34 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

const char	*rt_parse_err_str(enum e_rt_parse_error err)
{
	static const char	*err_strs[] = {
	[PARSE_ERR_OK] = "no error",
	[PARSE_ERR_ALLOC] = "allocation error",
	[PARSE_ERR_SYSCALL] = "system error",
	[PARSE_ERR_FILE] = "file format error",
	[PARSE_ERR_FILE_READ] = "file error",
	[PARSE_ERR_NULL] = "null pointer",
	[PARSE_ERR_UNKNOWN] = "unknown error",
	};

	if (err >= 0 && err < _PARSE_ERR_SIZE)
		return (err_strs[err]);
	return ("Unknown error");
}
