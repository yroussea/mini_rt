/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_coords.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:05:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 05:11:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#include <ft/math.h>
#include <rt/parser/primitive.h>

#define INVALID_CHAR_DIGIT "should be a digit"

#define INVALID_CHAR_E "exponent notation isn't supported"
#define FIX_E "replace the exponent notation with a decimal point"

t_rt_parser_file_context	rt_parser_ctx_char(size_t i, const char *err,
								const char *fix)
{
	t_rt_parser_file_context	ctx;

	ft_memset(&ctx, 0, sizeof(t_rt_parser_file_context));
	ctx.type = FILE_ERR_INVALID_CHAR;
	ctx.column = i;
	ctx.length = 1;
	ctx.error_message = err;
	ctx.possible_fix = fix;
	return (ctx);
}

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
		return (ERR_FILE(rt_parser_ctx_char(0, INVALID_CHAR_DIGIT, NULL)));
	*filled = true;
	num = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	*result = num;
	*strptr = str + i;
	return (res);
}

RESULT	rt_strtod_midcheck(const char *str)
{
	RESULT	res;

	if (str[0] == '.')
		return (OK());
	else if (str[0] == 'f' || str[0] == 'F')
		return (OK());
	else if (str[0] == 'e' || str[0] == 'E')
		return (ERR_FILE(rt_parser_ctx_char(0, INVALID_CHAR_E, FIX_E)));
	return (OK());
}

static RESULT	rt_strtod_expand(RESULT res, size_t len)
{
	if (RES_OK(res))
		return (res);
	else if (res.type == PARSE_ERR_FILE)
	{
		res.file_context.column += len;
	}
	return (res);
}

// Ex:
// ---
// 1.234f
// -1.f
// -.65
// +26.74f
// +1.f
//
// Invalids:
// ---
// .f
// .
// -.f
// +f
// AAAA-1.0f
// -AAAA1.0f
// -1AAAA.0f
// -1.AAAA0f
// -1.0AAAAf
// -1.0fAAAA
// -1A0f
RESULT	rt_strtod(const char *str, double *result, const char *end)
{
	double	parts[2];
	bool	filled[2];
	bool	neg;
	RESULT	res;
	char	*orig;

	ft_memset(filled, 0, sizeof(filled) / sizeof(filled[0]));
	orig = str;
	str += ft_strspn(str, " ");
	neg = (*str == '-');
	if (neg || *str == '+')
		str++;
	res = rt_strtoc_num(&str, &parts[0], &filled[0]);
	if (RES_OK(res))
		res = rt_strtod_midcheck(str);
	if (RES_OK(res) && str[0] == '.')
		res = rt_strtod_frac(&str, &parts[1], &filled[1]);
	if (RES_OK(res))
		res = rt_strtod_final(str, filled, end);
	if (neg)
	return (rt_strtod_expand(res, str - orig, result, parts));
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
