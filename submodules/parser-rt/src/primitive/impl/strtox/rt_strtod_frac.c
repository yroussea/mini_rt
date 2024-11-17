/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_frac.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:05:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 19:07:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

RESULT	rt_strtod_frac(const char **strptr, double *result, bool *filled,
			const char *end)
{
	RESULT		res;
	double		num;
	char		*str;
	size_t		i;

	res = OK();
	str = (char *)*strptr;
	if (str[0] != '.')
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DOT, NULL)));
	str++;
	*strptr = str;
	if (str[0] == 0 || (end && ft_strchr(end, str[0])))
		return (OK());
	if (str[0] == 'f' || str[0] == 'F')
		return (OK());
	if (!ft_isdigit(str[0]))
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
	*filled = true;
	num = 0;
	i = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*result = num;
	*strptr = str + i;
	return (res);
}
