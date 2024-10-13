/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_opt_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:52:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 04:14:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <rt/cli.h>
#include <rt/render/backend.h>
#include <unistd.h>

#if FEAT_CLI_FLAGS
# define CLI_USAGE "Usage: %s [-hvV] [-r <render_mode>] [-o <output_file>]\n\
 [--] [<input_file.rt>]\n\
\n\
\t-h                Display this help message.\n\
\t-v                Display the version of the program.\n\
\t-V                Increase the verbosity of the program. Can be used multiple \
\t                  times (max 2).\n\
\t-r <render_mode>  Set the render backend. Valid modes are:\n\
\t                  %s\n\
\t-o <output_file>  Set the output file. If set, the program will run in\n\
\t                  headless direct rendering mode, will render the scene to\n\
\t                  the output file and exit.\n\
\t--                Stop parsing flags.\n\
\n\
When no input file is specified, the program will run in application mode,\n\
which will bring up the main application menu.\n\
\n\
If an input file is specified, the program will run in direct rendering mode,\n\
and will render the scene in an editor window.\n\
"
#else
# define CLI_USAGE "Usage: %s [-h] [-v] [-V]\n\
[--] <input_file.rt>\n\
\n\
\t-h                Display this help message.\n\
\t-v                Display the version of the program.\n\
\t-V                Increase the verbosity of the program. Can be used multiple \
\t                  times (max 2).\n\
\t--                Stop parsing flags.\n\
\n\
When an input file is specified, the program will run in direct rendering mode,\n\
and will render the scene in an editor window.\n\
"
#endif // FEAT_CLI_FLAGS

void	rt_cli_opt_help(t_rt *rt)
{
	char					render_modes[2048];
	size_t					i;

	i = 0;
	ft_memset(render_modes, 0, sizeof(render_modes));
	while (g_backend_providers[i].name)
	{
		ft_strlcat(render_modes, g_backend_providers[i].name,
			sizeof(render_modes));
		if (g_backend_providers[i + 1].name)
			ft_strlcat(render_modes, ", ", sizeof(render_modes));
		i++;
	}
	ft_dprintf(STDERR_FILENO, CLI_USAGE, rt->executable, render_modes);
}
