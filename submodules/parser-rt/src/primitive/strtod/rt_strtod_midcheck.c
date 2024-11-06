/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_midcheck.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:05:51 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 14:37:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

// We're at the end of the first number part, this means
// we should have a few different cases:
// 1. We have a NULL terminator or a character in `end`, which means we're done.
// 3. We have a 'f' or 'F', which means we end after.
// 2. We have a decimal point, which means we're gonna have a fractional part.
// 3. We have an 'e' or 'E', which means we have an exponent (not good).
// 4. We have a character that isn't in `end`, which means 
//    it's an invalid character.
// (4.1. We have a digit. what???)
RESULT	rt_strtod_midcheck(const char *str, const char *end)
{
	RESULT	res;

	if (str[0] == 0 || (end && ft_strchr(end, str[0])))
		return (OK());
	if (str[0] == '.')
		return (OK());
	else if (str[0] == 'f' || str[0] == 'F')
		return (OK());
	else if (str[0] == 'e' || str[0] == 'E')
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_E, FIX_E)));
	return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
}
