/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 06:40:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 13:02:31 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <math.h>
#include <rt/parser/primitive/strtod.h>

#define INVALID_CHAR_OVERFLOW	"number is too large (overflow)"
#define INVALID_CHAR_UNDERFLOW	"number is too small (underflow)"

static RESULT	rt_strtoi_num(const char *orig, const char **strptr,
					const char *end, long long *resptr)
{
	RESULT		res;
	long long	result;
	const char	*str;

	str = *strptr;
	if (!*str || ft_strchr(end, *str))
		return (ERR_FILE(rt_strtod_ctx_char(str - orig, INVALID_CHAR_DIGIT,
					NULL)));
	result = 0;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	if (!*str || ft_strchr(end, *str))
	{
		*resptr = result;
		*strptr = str;
		res = OK();
	}
	else
		res = ERR_FILE(rt_strtod_ctx_char(str - orig, INVALID_CHAR_DIGIT, 0));
	return (res);
}

static RESULT	rt_strtoi_check_overflow(long long result, bool neg, size_t len)
{
	RESULT	res;

	if (len > 11)
	{
		if (neg)
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_OVERFLOW, 0));
		else
			res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_UNDERFLOW, 0));
	}
	if (result > INT_MAX)
		res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_OVERFLOW, 0));
	else if (result < INT_MIN)
		res = ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_UNDERFLOW, 0));
	if (RES_ERR(res))
		res.file_context.length = len;
	return (res);
}

RESULT	rt_strtoi(const char **strptr, int *resptr, const char *end)
{
	long long	result;
	bool		neg;
	RESULT		res;
	const char	*orig;
	const char	*str;

	result = 0;
	orig = *strptr;
	str = *strptr + ft_strspn(*strptr, " ");
	neg = (*str == '-');
	if (neg || *str == '+')
		str++;
	res = rt_strtoi_num(orig, &str, end, &result);
	if (RES_ERR(res))
		return (res);
	if (neg)
		result = -result;
	res = rt_strtoi_check_overflow(result, neg, str - orig);
	if (RES_ERR(res))
		return (res);
	*strptr = str;
	*resptr = (int)result;
	return (res);
}
