/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:39:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/10 23:40:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

const char	*rt_parse_err_str(t_rt_parser_error err)
{
	static const char	*err_strs[] = {
	[PARSER_ERR_OK] = "No error",
	[PARSER_ERR_ALLOC] = "Allocation error",
	[PARSER_ERR_SYSCALL] = "System error",
	[PARSER_ERR_FILE] = "File error",
	[PARSER_ERR_UNKNOWN] = "Unknown error",
	};

	if (err.type >= 0 && err.type < PARSER_ERR_SIZE)
		return (err_strs[err.type]);
	return ("Unknown error");
}
