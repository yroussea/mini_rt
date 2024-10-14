/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parse_file_target.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 05:34:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 06:11:21 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/opt.h>
#include <rt/cli.h>
#include <rt/features.h>
#include <rt/log.h>

int	rt_cli_parse_file_target(t_rt *rt, t_opt_globals *globals,
		t_opt_args *args)
{
	const int	argc = args->argc - globals->optind;
	const char	**argv = (const char **) args->argv + globals->optind;

	rt_trace(rt, "%s: argc: %d\n", __func__, argc);
	if (argc == 0 && FEAT_APPLICATION)
	{
		if (rt->flags.output)
			rt_error(rt, "-o: cannot specify output file with no input file\n");
		if (rt->flags.output)
			return (CLI_EXIT_FAILURE);
		rt_debug(rt, "cli: no input file provided, fallback to app mode\n");
		rt->flags.mode = RT_MODE_APP;
		return (CLI_PASS);
	}
	else if (argc == 0)
		rt_error(rt, "cli: no input file provided\n");
	else if (argc > 1)
		rt_error(rt, "cli: too many input files provided\n");
	else
	{
		rt->flags.filepath = argv[0];
		rt_debug(rt, "cli: input file: %s\n", rt->flags.filepath);
		return (CLI_PASS);
	}
	return (CLI_EXIT_FAILURE);
}
