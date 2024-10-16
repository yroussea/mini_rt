/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 02:03:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 06:08:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/app.h>
#include <rt/cli.h>
#include <rt/log.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <unistd.h>

static void	rt_dump_state(t_rt *rt)
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

static int	rt_init_backend(t_rt *rt)
{
	t_rt_backend_provider	*provider;

	rt_dump_state(rt);
	provider = rt_backend_provider_find(rt->flags.backend);
	if (provider == NULL)
	{
		rt_error(rt, "no backend provider found for '%s'\n",
			rt->flags.backend);
		return (1);
	}
	rt->backend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->backend != NULL && !rt->backend->init)
	{
		rt_error(rt, "backend provider '%s' does not have an init function\n",
			rt->flags.backend);
		return (1);
	}
	if (rt->backend == NULL || rt->backend->init(rt->backend))
	{
		rt_error(rt, "failed to initialize backend\n");
		return (1);
	}
	rt->queued_frontend = rt->flags.frontend;
	return (0);
}

static int	rt_init_frontend(t_rt *rt)
{
	t_rt_frontend_provider	*provider;

	provider = rt_frontend_provider_find(rt->queued_frontend);
	if (provider == NULL)
	{
		rt_error(rt, "no frontend provider found for '%s'\n",
			rt->queued_frontend);
		return (1);
	}
	rt->queued_frontend = NULL;
	rt->frontend = provider->fn(rt, provider->name, rt->width, rt->height);
	if (rt->frontend != NULL && !rt->frontend->init)
	{
		rt_error(rt, "frontend provider '%s' does not have an init function\n",
			provider->name);
		return (1);
	}
	if (rt->frontend == NULL || rt->frontend->init(rt->frontend))
	{
		rt_error(rt, "failed to initialize frontend\n");
		return (1);
	}
	return (0);
}

static int	rt_frontend_loop(t_rt *rt)
{
	int	ret;

	if (rt->frontend && rt->frontend->destroy)
		rt->frontend->destroy(rt->frontend);
	ret = rt_init_frontend(rt);
	if (ret != 0)
		return (ret);
	rt_trace(rt, "cli: handing off to frontend %s\n",
		rt->frontend->name);
	rt->frontend->handoff(rt->frontend);
	if (rt->frontend->destroy)
		rt->frontend->destroy(rt->frontend);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_rt	rt;
	int		ret;

	ret = 0;
	if (!rt_init(&rt, argc, argv, envp))
	{
		ret = rt_cli_parse(&rt, argc, argv);
		if (ret > 0)
			ret = (ret - 1);
		else
		{
			ret = rt_init_backend(&rt);
			while (!ret && rt.queued_frontend)
				ret = rt_frontend_loop(&rt);
		}
	}
	rt_destroy(&rt);
	return (ret);
}
