/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 20:55:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/math.h>
#include <rt/parser/primitive.h>

#define INVALID_CHAR_DIGIT "should be a digit"
#define INVALID_CHAR_E "exponent notation isn't supported"
#define FIX_E "replace the exponent notation with a decimal point"


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

RESULT	rt_strtod_frac(const char **strptr, double *result, bool *filled)
{
	RESULT	res;
	double	num;
	char	*str;

	res = OK();
	str = *strptr;
	if (!ft_isdigit(str[0]))
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
	*filled = true;
	num = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*result = num / ft_pow(10, i);
	*strptr = str + i;
	return (res);
}

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

	if (str[0] == 0 || ft_strchr(end, str[0]))
		return (OK());
	if (str[0] == '.')
		return (OK());
	else if (str[0] == 'f' || str[0] == 'F')
		return (OK());
	else if (str[0] == 'e' || str[0] == 'E')
		return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_E, FIX_E)));
	return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
}

static RESULT	rt_strtod_final(const char *str, bool *filled, const char *end)
{
	if (!filled[0] && !filled[1])
	if (str[0] == NULL || ft_strchr(end, str[0]))
		return (OK());
}

/**
 * @brief Parses a segment of a coordinate string.
 *
 * @param slice Pointer to the string slice from which to parse.
 * @param stop The charset to stop parsing at.
 * @param result The result to write to.
 *
 * @return A result.
 */
static RESULT	rt_parser_coords_segment(const char **slice, double *result,
					const char *stop)
{
	char	*contents;

	contents = *slice;

	return (OK());
}

// Format %f,%f,%f
static RESULT	rt_parser_prim_coords(t_rt_parser *parser, const char *slice,
				void *memory, size_t *size)
{
	double	results[3];
	RESULT	res;

	res = rt_parser_coords_segment(&slice, &results[0], ",");
	if (RES_ERR(res))
		return (res);
	return (res);
}

__attribute__((constructor))
void	rt_parser_prim_coords_init(void)
{
	rt_parser_global_primitive(RT_PRIM_COORDINATES, rt_parser_prim_coords);
}
