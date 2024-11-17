/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:03:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:26:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/app.h>
#include <rt/cli.h>
#include <rt/cli/parse/rt.h>
#include <rt/log.h>
#include <rt/objects.h>
#include <rt/parser.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <rt/util.h>
#include <unistd.h>

void		rt_parser_dump_state(const t_rt *rt, t_rt_parser *parser);

static int	rt_parse_wrap(const t_rt *rt, t_list **result)
{
	RESULT		res;

	__attribute__((cleanup(rt_parser_destroy)))
	t_rt_parser parser;
	if (rt->flags.mode == RT_MODE_APP)
		return (0);
	res = rt_parser_init(&parser, rt, (t_parser_name_fn *)(void *)
			rt_object_strtype, true);
	if (RES_OK(res))
		res = rt_cli_parser_rt_init(&parser);
	if (RES_OK(res))
		res = rt_parser_parse(&parser, rt->flags.filepath);
	if (!RES_OK(res))
	{
		ERROR_PRINT(&parser, res);
		ft_lst_free(&parser.result, rt_free_aligned);
		return (res.type);
	}
	rt_parser_dump_state(rt, &parser);
	if (rt->flags.mode == RT_MODE_PARSER_TEST)
		ft_lst_free(&parser.result, rt_free_aligned);
	else
		*result = parser.result;
	return (0);
}

static void	rt_dump_state(const t_rt *rt)
{
	rt_debug(rt, "launching rt in mode %d\n", rt->flags.mode);
	rt_debug(rt, "input file is '%s'\n", rt->flags.filepath);
	if (rt->flags.mode == RT_MODE_RENDER_ONCE)
		rt_debug(rt, "output file is '%s'\n", rt->flags.output);
	rt_debug(rt, "frontend is '%s'\n", rt->flags.frontend);
	rt_debug(rt, "backend is '%s'\n", rt->flags.backend);
}

static int	rt_frontend_loop(t_rt *rt)
{
	int	ret;

	if (rt->frontend && rt->frontend->destroy)
		rt->frontend->destroy(rt->frontend);
	ret = rt_frontend_init(rt);
	if (ret != 0)
		return (ret);
	rt_trace(rt, "cli: handing off to frontend %s\n",
		rt->frontend->name);
	rt->frontend->handoff(rt->frontend);
	if (rt->frontend->destroy)
		rt->frontend->destroy(rt->frontend);
	return (ret);
}

static void	rt_cleanup_objects(t_list **objects)
{
	ft_lst_free(objects, NULL);
}

int	main(int argc, const char **argv, const char **envp)
{
	int		ret;

	__attribute__((cleanup(rt_cleanup_objects))) t_list * result = NULL;
	__attribute__((cleanup(rt_destroy))) t_rt rt;
	ret = 0;
	if (!rt_init(&rt, argc, argv, envp))
	{
		ret = rt_cli_parse(&rt, argc, argv);
		if (ret > 0)
			ret = (ret - 1);
		else
		{
			ret = rt_parse_wrap(&rt, &result);
			if (ret != 0 || rt.flags.mode == RT_MODE_PARSER_TEST)
				return (ret);
			rt_dump_state(&rt);
			ret = rt_backend_init(&rt, result);
			while (!ret && rt.queued_frontend)
				ret = rt_frontend_loop(&rt);
		}
	}
	return (ret);
}
