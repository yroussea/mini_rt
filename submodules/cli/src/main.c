/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:03:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 17:26:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/app.h>
#include <rt/cli.h>
#include <rt/log.h>
#include <rt/parser.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <unistd.h>

int	rt_backend_init(const t_rt *rt);
int	rt_frontend_init(const t_rt *rt);

static int	rt_parse_wrap(const t_rt *rt)
{
	RESULT		res;

	__attribute__((cleanup(rt_parser_destroy))) t_rt_parser parser;
	if (rt->flags.mode == RT_MODE_APP)
		return (0);
	res = rt_parser_init(&parser, rt);
	if (RES_OK(res))
		res = rt_parser_parse(&parser, rt->flags.filepath);
	if (!RES_OK(res))
	{
		ERROR_PRINT(&parser, res);
		return (res.type);
	}
	return (0);
}

static void	rt_dump_state(const t_rt *rt)
{
	rt_trace(rt, "%s: launching rt in mode %d\n", __func__,
		rt->flags.mode);
	rt_trace(rt, "%s: input file is '%s'\n", __func__,
		rt->flags.filepath);
	if (rt->flags.mode == RT_MODE_RENDER_ONCE)
		rt_trace(rt, "%s: output file is '%s'\n", __func__,
			rt->flags.output);
	rt_trace(rt, "%s: frontend is '%s'\n", __func__,
		rt->flags.frontend);
	rt_trace(rt, "%s: backend is '%s'\n", __func__,
		rt->flags.backend);
}

static int	rt_frontend_loop(const t_rt *rt)
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

int	main(int argc, const char **argv, const char **envp)
{
	int		ret;

	__attribute__((cleanup(rt_destroy))) t_rt rt;
	ret = 0;
	if (!rt_init(&rt, argc, argv, envp))
	{
		ret = rt_cli_parse(&rt, argc, argv);
		if (ret > 0)
			ret = (ret - 1);
		else
		{
			ret = rt_parse_wrap(&rt);
			if (ret != 0)
				return (ret);
			if (rt.flags.mode == RT_MODE_PARSER_TEST)
				return (ret);
			rt_dump_state(&rt);
			ret = rt_backend_init(&rt);
			while (!ret && rt.queued_frontend)
				ret = rt_frontend_loop(&rt);
		}
	}
	return (ret);
}
