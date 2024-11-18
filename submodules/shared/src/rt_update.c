/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:45:50 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 23:47:33 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEVMODE
# define RT_DEVMODE 0
#endif // !RT_DEVMODE

#if RT_DEVMODE
# include <rt/devreload.h>
#endif // RT_DEVMODE

#include <rt/log.h>
#include <rt/parser.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <rt/util.h>
#include <sys/stat.h>

#if !RT_DEVMODE

void	rt_devrl_check_reload(void *a);

#endif // !RT_DEVMODE

static bool	rt_parser_check_reload(t_rt *rt)
{
	struct stat		st;
	int				ret;
	static time_t	mtime = 0;
	static int		init = 0;

	if (rt && rt->flags.mode == RT_MODE_PARSER_TEST)
		return (false);
	ret = rt_stat(rt->flags.filepath, &st);
	if (ret == -1)
		return (false);
	if (st.st_mtime > mtime)
	{
		mtime = st.st_mtime;
		if (init == 0)
		{
			init = 1;
			return (false);
		}
		rt_trace(rt, "found modification on %s\n", rt->flags.filepath);
		return (true);
	}
	return (false);
}

void	rt_parser_dump_state(const t_rt *rt, t_rt_parser *parser);

static RESULT	rt_reparse(t_rt *rt, t_rt_parser *parser,
					const char *filepath)
{
	RESULT	res;

	res = rt_parser_parse(parser, filepath);
	if (!RES_OK(res))
	{
		ERROR_PRINT(parser, res);
		ft_lst_free(&parser->result, rt_free_aligned);
		return (res);
	}
	rt_parser_dump_state(rt, parser);
	return (res);
}

void	rt_parser_cleanup(t_rt_parser *parser);
void	rt_destroy_objects(t_obj *objects);
void	rt_backend_init_switch(t_rt *rt);
t_obj	*rt_object_list(t_list *objects);

static void	rt_backend_morph(t_rt *rt, t_rt_parser *parser,
				t_rt_backend *backend, const char *name)
{
	t_rt_backend_provider	*provider;
	t_rt_backend			fake;

	provider = rt_backend_provider_find(name);
	if (provider == NULL)
	{
		rt_error(rt, "no backend provider found for %s\n", name);
		return ;
	}
	rt_trace(rt, "switching backend to %s\n", name);
	rt_backend_handoff(backend, &fake);
	fake.objects = rt_object_list(parser->result);
	fake.main_camera = NULL;
	if (backend->destroy)
		backend->destroy(backend);
	rt->backend = provider->fn(rt, provider->name, fake.width, fake.height);
	if (!rt->backend)
		rt_error(rt, "failed to create backend\n");
	else if (rt->backend->init)
	{
		rt_backend_handoff(&fake, rt->backend);
		rt_backend_init_switch(rt);
	}
}

void	rt_update(t_rt *rt)
{
	RESULT	res;

	if (RT_DEVMODE && rt)
		rt_devrl_check_reload(rt);
	if (rt_parser_check_reload(rt))
	{
		rt_parser_cleanup(rt->parser);
		res = rt_reparse(rt, rt->parser, rt->flags.filepath);
		if (RES_ERR(res))
			rt_error(rt, "couldn't parse file %s\n", rt->flags.filepath);
		else
		{
			rt_info(rt, "successfully reparsed file %s\n", rt->flags.filepath);
			rt_backend_morph(rt, rt->parser, rt->backend, rt->backend->name);
		}
	}
}
