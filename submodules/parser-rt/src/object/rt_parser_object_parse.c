/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_object_parse.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 07:03:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/15 18:38:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser.h>

static RESULT	rt_parser_object_parse_step(t_rt_object_parser *objp,
					char *token, void **memory)
{
	(void)objp;
	(void)token;
	(void)memory;
	return (OK());
}

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

static RESULT	rt_parser_object_reset_optional_failure(t_rt_object_parser *objp,
					RESULT res)
{
	if (RES_OK(res))
		res = OK();
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
	RESULT	tmp;
	RESULT	err;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	res = OK();
	err = OK();
	while (RES_OK(res) && tokens[i] && j < objp->sequence_size)
	{
		tmp = rt_parser_object_parse_step(objp, tokens[i], &memory);
		if (RES_OK(tmp))
			err = rt_parser_object_reset_optional_failure(objp, tmp, err);
		else if (j < objp->required)
			res = tmp;
		else if (RES_OK(err))
			err = tmp;
		j++;
		i += RES_OK(err);
	}
	if (RES_OK(err))
		return (rt_parser_object_check_complete(objp, line, err));
	return (err);
}

RESULT	rt_parser_object_parse(t_rt_object_parser *objp, char **tokens,
			const char *line)
{
	RESULT	res;
	void	*memory;

	memory = ft_calloc(objp->size, sizeof(char));
	if (!memory)
		return (ERRS(PARSE_ERR_ALLOC, "cannot allocate memory for object"));
	res = rt_parser_object_parse_all(objp, tokens, line, memory);
	if (RES_OK(res))
		ft_lst_tadd(&objp->parser->result, memory);
	return (res);
}
