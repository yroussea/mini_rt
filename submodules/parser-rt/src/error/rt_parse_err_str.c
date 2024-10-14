/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:39:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/12 02:45:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

const char	*rt_parse_err_str(enum e_rt_parse_error err)
{
	static const char	*err_strs[] = {
	[PARSE_ERR_OK] = "No error",
	[PARSE_ERR_ALLOC] = "Allocation error",
	[PARSE_ERR_SYSCALL] = "System error",
	[PARSE_ERR_FILE] = "File error",
	[PARSE_ERR_UNKNOWN] = "Unknown error",
	};

	if (err >= 0 && err < _PARSE_ERR_SIZE)
		return (err_strs[err]);
	return ("Unknown error");
}
