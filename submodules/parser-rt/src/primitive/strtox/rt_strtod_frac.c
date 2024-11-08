/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_frac.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:05:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 20:01:51 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

RESULT	rt_strtod_frac(const char **strptr, double *result, bool *filled)
{
	RESULT		res;
	double		num;
	const char	*str;
	size_t		i;

	res = OK();
	str = *strptr;
	if (!ft_isdigit(str[0]))
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
	*filled = true;
	num = 0;
	i = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*result = num / ft_pow(10, i);
	*strptr = str + i;
	return (res);
}
