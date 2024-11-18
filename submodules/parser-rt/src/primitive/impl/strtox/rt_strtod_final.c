/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_strtod_final.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:30:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 18:31:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>

static t_rt_parser_file_context	rt_strtod_final_no_filled(const char *str,
			const char *orig)
{
	t_rt_parser_file_context	ctx;

	ft_memset(&ctx, 0, sizeof(t_rt_parser_file_context));
	ctx.type = FILE_ERR_MISSING_PART;
	ctx.error_message = ft_strdup(INVALID_MISSING_PARTS);
	ctx.possible_fix = FIX_MISSING_PARTS;
	ctx.length = ft_strlen(orig);
	ctx.column = (orig - str);
	return (ctx);
}

RESULT	rt_strtod_final(const char **strptr, bool *filled, const char *end,
			const char *orig)
{
	const char	*str = *strptr;

	if (!filled[0] && !filled[1])
		return (ERR_FILE(rt_strtod_final_no_filled(str, orig)));
	if (!str[0] || (end && ft_strchr(end, str[0])))
		return (OK());
	if (str[0] == 'f' || str[0] == 'F')
	{
		str++;
		*strptr = str;
		if (!str[0] || (end && ft_strchr(end, str[0])))
			return (OK());
	}
	return (ERR_FILE(rt_strtod_ctx_char(0, INVALID_CHAR_END, NULL)));
}
