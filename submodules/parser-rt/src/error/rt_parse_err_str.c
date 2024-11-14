/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:39:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:04:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

const char	*rt_parse_err_str(enum e_rt_parse_error err)
{
	static const char	*err_strs[] = {
	[PARSE_ERR_OK] = "no error occured, why are you seeing this?",
	[PARSE_ERR_ALLOC] = "an allocation error occured",
	[PARSE_ERR_SYSCALL] = "a system error occured",
	[PARSE_ERR_FILE] = "generic file format error",
	[PARSE_ERR_FILE_READ] = "an error occured while reading a file",
	[PARSE_ERR_BAD_USAGE] = "bad parser library usage noob",
	[PARSE_ERR_NULL] = "a null pointer was passed",
	[PARSE_ERR_UNKNOWN] = "an unknown error occured",
	};

	if (err >= 0 && err < _PARSE_ERR_SIZE)
		return (err_strs[err]);
	return ("Unknown error");
}
