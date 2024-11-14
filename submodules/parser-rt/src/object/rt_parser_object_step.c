/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_step.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 06:59:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 07:05:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser.h>
#include <stdbool.h>

static RESULT	rt_parser_object_step0(t_rt_object_parser *objp, size_t offset,
					enum e_rt_primitive type, bool required)
{
	if (!objp)
		return (ERRS(PARSE_ERR_NULL, "invalid object parser pointer passed to"
				"rt_parser_object_step0"));
	if (objp->sequence_size != objp->required && required)
		return (ERRS(PARSE_ERR_BAD_USAGE, "cannot ask for a required param"
				"after an optional one"));
	objp->sequence[objp->sequence_size].type = type;
	objp->sequence[objp->sequence_size].offset = offset;
	objp->sequence_size++;
	if (required)
		objp->required++;
	return (OK());
}

RESULT	rt_parser_object_step_opt(t_rt_object_parser *parser, size_t offset,
			enum e_rt_primitive type)
{
	return (rt_parser_object_step0(parser, offset, type, false));
}

RESULT	rt_parser_object_step(t_rt_object_parser *parser, size_t offset,
			enum e_rt_primitive type)
{
	return (rt_parser_object_step0(parser, offset, type, true));
}
