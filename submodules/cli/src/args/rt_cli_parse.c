/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:55:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:15:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/opt.h>
#include <ft/string.h>
#include <rt/cli.h>
#include <rt/log.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>

int		rt_cli_parse_file_target(t_rt *rt, t_opt_globals *globals,
			t_opt_args *args);

int		rt_cli_parse_frontend(t_rt *rt, char *frontend);
int		rt_cli_parse_backend(t_rt *rt, char *backend);

static int	rt_cli_parse_invalid(t_rt *rt, t_opt_globals *globals)
{
	if (ft_strchr(CLI_ARG_OPTS, globals->optopt))
		rt_error(rt, "-%c: option requires an argument\n",
			globals->optopt);
	else
		rt_error(rt, "-%c: invalid option\n", globals->optopt);
	rt_cli_opt_help(rt);
	return (CLI_EXIT_FAILURE);
}

static int	rt_cli_parse_opt(t_rt *rt, t_opt_globals *globals, int opt)
{
	if (opt == 'V')
		rt->flags.verbosity++;
	else if (opt == 'b')
		return (rt_cli_parse_backend(rt, globals->optarg));
	else if (opt == 'f')
		return (rt_cli_parse_frontend(rt, globals->optarg));
	else if (opt == 'p')
		rt->flags.mode = RT_MODE_PARSER_TEST;
	else if (opt == 'o')
	{
		rt->flags.mode = RT_MODE_RENDER_ONCE;
		rt->flags.output = globals->optarg;
	}
	else if (opt == 'n')
		rt->flags.no_unique = true;
	else if (opt == '?')
		return (rt_cli_parse_invalid(rt, globals));
	return (CLI_PASS);
}

static int	rt_cli_parse_flags(t_rt *rt, t_opt_globals *globals,
				t_opt_args *args)
{
	int	i;
	int	ret;

	ret = 0;
	while (true)
	{
		i = ft_opt_get(globals, args);
		if (i == -1)
			break ;
		rt_trace(rt, "cli: parsing flag %c\n", i);
		if (i == HELP_OPT || i == 'h')
			rt_cli_opt_help(rt);
		else if (i == 'v')
			rt_cli_opt_version(rt);
		else
		{
			ret = rt_cli_parse_opt(rt, globals, i);
			if (ret != CLI_PASS)
				break ;
			continue ;
		}
		ret = CLI_EXIT_SUCCESS;
		break ;
	}
	return (ret);
}

int	rt_cli_parse(t_rt *rt, int argc, const char **argv)
{
	t_opt_globals	globals;
	t_opt_args		args;
	int				ret;

	if (argc == 1)
	{
		if (!FEAT_APPLICATION)
		{
			rt_error(rt, "no arguments provided\n");
			return (CLI_EXIT_FAILURE);
		}
		return (CLI_EXIT_SUCCESS);
	}
	args = ft_opt_args(argc, (char **)argv, OPT_BASH_LIKE, CLI_VALID_OPTS);
	globals = ft_opt_globals();
	globals.opterr = 0;
	ret = rt_cli_parse_flags(rt, &globals, &args);
	if (ret == CLI_PASS)
		return (rt_cli_parse_file_target(rt, &globals, &args));
	return (ret);
}
