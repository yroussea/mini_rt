/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:55:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 03:53:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/opt.h>
#include <rt/cli.h>
#include <rt/log.h>
# include <stdio.h>

#define CLI_PASS			0
#define CLI_EXIT_SUCCESS	1
#define CLI_EXIT_FAILURE	2

static int	rt_cli_parse_opt(t_rt *rt, t_opt_globals *globals, int opt)
{
	if (opt == 'V')
		rt->flags.verbosity++;
	else if (opt == 'r')
	{
		printf("rt_cli_parse_opt: r '%s'\n", globals->optarg);
	}
	else if (opt == 'o')
	{
		printf("rt_cli_parse_opt: o '%s'\n", globals->optarg);
		rt->flags.output = globals->optarg;
	}
	else
	{
		rt_error(rt, "invalid option '%c'\n", opt);
		return (CLI_EXIT_FAILURE);
	}
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

int	rt_cli_parse(t_rt *rt, int argc, char **argv)
{
	t_opt_globals	globals;
	t_opt_args		args;

	if (argc == 1)
	{
		if (!FEAT_APPLICATION)
		{
			rt_error(rt, "no arguments provided\n");
			return (CLI_EXIT_FAILURE);
		}
		return (CLI_EXIT_SUCCESS);
	}
	args = ft_opt_args(argc, argv, OPT_BASH_LIKE, CLI_VALID_OPTS);
	globals = ft_opt_globals();
	globals.opterr = 0;
	return (rt_cli_parse_flags(rt, &globals, &args));
}
