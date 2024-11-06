/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 20:18:28 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 20:51:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/string.h>
#include <rt/parser/error.h>

t_rt_parser_file_context	rt_strtod_ctx_char(size_t i, const char *err,
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

static RESULT	rt_strtod_expand(RESULT res, size_t len)
{
	if (RES_OK(res))
		return (res);
	else if (res.type == PARSE_ERR_FILE)
		res.file_context.column += len;
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
RESULT	rt_strtod(const char *str, double *result, const char *end)
{
	double	parts[2];
	bool	filled[2];
	bool	neg;
	RESULT	res;
	char	*orig;

	ft_memset(parts, 0, sizeof(parts));
	ft_memset(filled, 0, sizeof(filled));
	orig = str;
	str += ft_strspn(str, " ");
	neg = (*str == '-');
	if (neg || *str == '+')
		str++;
	res = rt_strtoc_num(&str, &parts[0], &filled[0]);
	if (RES_OK(res))
		res = rt_strtod_midcheck(str, end);
	if (RES_OK(res) && str[0] == '.')
		res = rt_strtod_frac(&str, &parts[1], &filled[1], end);
	if (RES_OK(res))
		res = rt_strtod_final(str, filled, end);
	res = rt_strtod_expand(res, str - orig, result, parts);
	if (neg && RES_OK(res))
		*result = -(*result);
	return (res);
}
