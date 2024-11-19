/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:03:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:32:04 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <rt/util.h>

t_rt_parser_file_context
rt_parser_object_unexpected_optional(const char *token);

RESULT
rt_parser_object_incomplete(t_rt_object_parser_step *step,
	char **tokens, const char *line, size_t ntok);

static RESULT	rt_parser_object_expand_step(RESULT res, size_t itkn,
					const char *line)
{
	if (RES_OK(res))
		return (res);
	if (res.type == PARSE_ERR_FILE)
	{
		res.file_context.column += rt_parser_line_token_pos(line, itkn);
	}
	return (res);
}

static RESULT	rt_parser_object_optional_errors(t_rt_object_parser *objp,
					RESULT res, RESULT last)
{
	if (RES_ERR(res))
	{
		if (RES_ERR(last))
			rt_parse_err_free(objp->parser, res);
		else
			return (res);
		return (last);
	}
	return (res);
}

static RESULT	rt_parser_object_parse_optional(t_rt_object_parser *objp,
					char **tokens, void *memory, size_t *itkn)
{
	RESULT	res;
	RESULT	last;
	size_t	iseq;

	iseq = objp->required;
	res = OK();
	last = OK();
	while (tokens[*itkn] && iseq < objp->sequence_size)
	{
		res = rt_parser_object_parse_step(objp, tokens[*itkn], iseq, memory);
		*itkn += RES_OK(res);
		iseq++;
		if (RES_OK(last))
			last = res;
		else if (RES_ERR(res))
			rt_parse_err_free(objp->parser, res);
	}
	if (tokens[*itkn] != NULL)
		return (ERR_FILE(rt_parser_object_unexpected_optional(tokens[*itkn])));
	return (rt_parser_object_optional_errors(objp, res, last));
}

// Let's say we have this object declaration...
//
// # sphere     center		  radius  [color]       [material]
//   sp         0.0 0.0 0.0   10.4    0.0 0.0 1.0   checkered
//
// ...where both the `color` and `material` parts are optional.
//
// We want failed optional parts to be ignored, so we can try to parse
// the next part, maybe throwing a warning. However, if every part
// afterwards fails, we want to return the error of the first
// failed part.
//
// So something like:
//
// # sphere     center		  radius  [color]       [material]
//   sp         0.0 0.0 0.0   10.4                  checkered
//
// Would error on the color parsing, but be okay overall.
static RESULT	rt_parser_object_parse_all(t_rt_object_parser *objp,
					char **tokens, const char *line, void *memory)
{
	RESULT	res;
	size_t	itkn;
	size_t	iseq;

	res = OK();
	itkn = 1;
	iseq = 0;
	*((uint32_t *)memory) = objp->enum_id;
	while (RES_OK(res) && tokens[itkn] && iseq < objp->required)
	{
		res = rt_parser_object_parse_step(objp, tokens[itkn], iseq, memory);
		res = rt_parser_object_expand_step(res, itkn, line);
		itkn++;
		iseq++;
	}
	if (RES_OK(res) && iseq < objp->required)
		res = rt_parser_object_incomplete(&objp->sequence[iseq],
				tokens, line, itkn);
	if (RES_OK(res) && objp->required < objp->sequence_size)
	{
		res = rt_parser_object_parse_optional(objp, tokens, memory, &itkn);
		res = rt_parser_object_expand_step(res, itkn, line);
	}
	return (res);
}

// static RESULT	rt_parser_object_parse_all(t_rt_object_parser *objp,
// 					char **tokens, const char *line, void *memory)
// {
// 	RESULT	res;
// 	RESULT	tmp;
// 	RESULT	err;
// 	size_t	i;
// 	size_t	j;
//
// 	j = 0;
// 	i = 0;
// 	res = OK();
// 	err = OK();
// 	while (RES_OK(res) && tokens[i] && j < objp->sequence_size)
// 	{
// 		rt_debug(objp->parser->rt, "pall: parsing tkn[%d] with seq[%d]\n",
// 			(int) i, (int) j);
// 		tmp = rt_parser_object_parse_step(objp, tokens[i], j, &memory);
// 		if (RES_OK(tmp))
// 			err = rt_parser_object_reset_optional_failure(objp, tmp, err);
// 		else if (j < objp->required)
// 			res = tmp;
// 		else if (RES_OK(err))
// 			err = tmp;
// 		j++;
// 		i += RES_OK(err);
// 	}
// 	if (RES_OK(err))
// 		return (rt_parser_object_check_complete(objp, line, res));
// 	return (err);
// }

RESULT	rt_parser_object_parse(t_rt_object_parser *objp, char **tokens,
			const char *line)
{
	const t_rt_parser	*parser = objp->parser;
	RESULT				res;
	void				*memory;
	const char			*name;

	name = objp->id;
	if (parser->name_fn)
		name = parser->name_fn(objp->enum_id);
	rt_trace(parser->rt, "allocating %d bytes for object '%s'\n",
		(int) objp->size, name);
	memory = rt_malloc_aligned(objp->size, 32);
	if (!memory)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate memory for object"));
	res = rt_parser_object_parse_all(objp, tokens, line, memory);
	if (RES_OK(res) && ft_lst_tadd(&objp->parser->result, memory))
		rt_debug(parser->rt, "successfully parsed object '%s'\n", name);
	else
	{
		rt_free_aligned(memory);
		if (RES_OK(res))
			res = ERRS(PARSE_ERR_ALLOC, "cannot allocate memory for obj node");
	}
	return (res);
}
