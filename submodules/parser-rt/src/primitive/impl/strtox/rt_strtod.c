/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:18:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 07:02:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <rt/parser/primitive/strtod.h>

t_rt_parser_file_context	rt_strtod_ctx_char(size_t i, const char *err,
								const char *fix)
{
	t_rt_parser_file_context	ctx;

	ft_memset(&ctx, 0, sizeof(t_rt_parser_file_context));
	ctx.type = FILE_ERR_INVALID_CHAR;
	ctx.column = i;
	ctx.length = 1;
	ctx.error_message = err;
	ctx.possible_fix = (char *) fix;
	return (ctx);
}

static RESULT	rt_strtod_expand(RESULT res, size_t len, double *result,
					double parts[2])
{
	double	total;

	if (RES_OK(res))
	{
		total = parts[0];
		if (parts[1] != 0)
			total += parts[1] / pow(10, ft_lllen((long long)parts[1]));
		*result = total;
		return (res);
	}
	else if (res.type == PARSE_ERR_FILE)
		res.file_context.column += len;
	return (res);
}

// num: read the number
// midcheck: check if we're at the middle '.' or at the end
// frac: if we're at the '.', read the fractional part
// final: check if we're at a valid end
// expand: error expansion + result handling
RESULT	rt_strtod(const char **str, double *result, const char *end)
{
	double		parts[2];
	bool		filled[2];
	bool		neg;
	RESULT		res;
	const char	*orig;

	ft_memset(parts, 0, sizeof(parts));
	ft_memset(filled, 0, sizeof(filled));
	orig = *str;
	*str += ft_strspn(*str, " ");
	neg = (**str == '-');
	if (neg || **str == '+')
		(*str)++;
	res = rt_strtod_num(str, &parts[0], &filled[0]);
	if (RES_OK(res))
		res = rt_strtod_midcheck(*str, end);
	if (RES_OK(res) && **str == '.')
		res = rt_strtod_frac(str, &parts[1], &filled[1]);
	if (RES_OK(res))
		res = rt_strtod_final(str, filled, end);
	res = rt_strtod_expand(res, *str - orig, result, parts);
	if (neg && RES_OK(res))
		*result = -(*result);
	return (res);
}

// Valid:
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
