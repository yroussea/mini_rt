/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_parse_step.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 03:37:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/16 03:37:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#include <rt/parser.h>

static const t_rt_primitive_parser	*rt_parser_prim_get(
	const t_rt_parser *parser,
	const enum e_rt_primitive type
) {
	size_t						i;
	const t_rt_primitive_parser	*primp;

	i = 0;
	primp = &parser->primitive_parsers[i];
	while (primp->fn)
	{
		if (primp->type == type)
			return (primp);
		i++;
		primp = &parser->primitive_parsers[i];
	}
	return (NULL);
}

RESULT	rt_parser_object_parse_step(t_rt_object_parser *objp,
			char *token, size_t index, void **memory)
{
	const t_rt_parser				*parser = objp->parser;
	const t_rt_object_parser_step	step = objp->sequence[index];
	const t_rt_primitive_parser		*primp = rt_parser_prim_get(parser,
			step.type);
	RESULT							res;
	size_t							size;

	if (!primp || !primp->fn)
		return (ERRS(PARSE_ERR_UNKNOWN, "unknown primitive type "
				"'%s' for token '%s'\n", rt_parser_strprim(step.type), token));
	rt_trace(parser->rt, "running parse step '%s' on token '%s'\n",
		rt_parser_strprim(step.type), token);
	size = 0;
	res = primp->fn(parser, token, memory, &size);
	if (RES_OK(res))
		*memory = *memory + size;
	else
		rt_trace(parser->rt, "failed to parse '%s'\n", token);
	return (res);
}
