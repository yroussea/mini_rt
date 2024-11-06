/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_final.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 14:52:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

RESULT	rt_strtod_final(const char **strptr, bool *filled, const char *end)
{
	char	*str;

	if (!filled[0] && !filled[1])
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_MISSING_PARTS,
					FIX_MISSING_PARTS)));
	str = *strptr;
	if (str[0] == NULL || (end && ft_strchr(end, str[0])))
		return (OK());
	if (str[0] == 'f' || str[0] == 'F')
	{
		*strptr = str + 1;
		return (OK());
	}
	return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_END, NULL)));
}
