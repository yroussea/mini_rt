/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:04:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 14:05:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

RESULT	rt_strtod_num(const char **strptr, double *result, bool *filled)
{
	RESULT	res;
	double	num;
	char	*str;

	res = OK();
	str = *strptr;
	if (*str == '.')
		return (res);
	if (!ft_isdigit(str[0]))
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
	*filled = true;
	num = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*result = num;
	*strptr = str + i;
	return (res);
}
