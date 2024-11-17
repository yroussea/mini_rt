/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:03:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:29:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <rt/util.h>

static RESULT	rt_parser_object_check_complete(t_rt_object_parser *objp,
					const char *line, RESULT res)
{
	if (RES_OK(res))
	{
		(void)objp;
		(void)line;
	}
	return (res);
}

static RESULT	rt_parser_object_parse_optional(t_rt_object_parser *objp,
					char **tokens, void *memory)
{
	(void)objp, (void)tokens, (void)memory;
	return (OK());
}

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
	res = rt_parser_object_check_complete(objp, line, res);
	if (RES_OK(res) && objp->required < objp->sequence_size)
		return (rt_parser_object_parse_optional(objp, tokens + itkn, memory));
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
		free(memory);
		if (RES_OK(res))
			res = ERRS(PARSE_ERR_ALLOC, "cannot allocate memory for obj node");
	}
	return (res);
}
