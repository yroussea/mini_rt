/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_opt_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:52:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:25:08 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <ft/print.h>
#include <ft/string.h>
#include <rt/cli.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>
#include <unistd.h>

#if FEAT_CLI_FLAGS
# if 0
#  define CLI_USAGE "Usage: %s [-hvV] [-pn] [-b <backend>] [-f <frontend>] \
[-o <output_file>] <input_file.rt>\n\
\n\
\t-h                Display this help message.\n\
\t-v                Display the version of the program.\n\
\t-V                Increase the verbosity of the program,\n\
\t                  can be used multiple times (max 3).\n\
\t-p                Run the program in parser-test mode,\n\
\t                  this is used for debugging.\n\
\t-n                Allows usage of multiple unique objects\n\
\t                  like cameras and lights. (tip: use the arrow\n\
\t                  keys to cycle through available cameras)\n\
\t-b <backend>      Set the render backend. Valid modes are:\n\
\t                  %s\n\
\t-f <frontend>     Set the frontend. Valid modes are:\n\
\t                  %s\n\
\t-o <output_file>  Set the output file. If set, the program will run in\n\
\t                  headless direct rendering mode, will render the scene to\n\
\t                  the output file and exit.\n\
\n\
When no input file is specified, the program will run in application mode,\n\
which will bring up the main application menu.\n\
\n\
If an input file is specified, the program will run in direct rendering mode,\n\
and will render the scene in an editor window.\n\
"
# else
#  define CLI_USAGE "Usage: %s [-hvV] [-pn] [-b <backend>] [-f <frontend>] \
<input_file.rt>\n\
\n\
\t-h                Display this help message.\n\
\t-v                Display the version of the program.\n\
\t-V                Increase the verbosity of the program,\n\
\t                  can be used multiple times (max 3).\n\
\t-p                Run the program in parser-test mode,\n\
\t                  this is used for debugging.\n\
\t-n                Allows usage of multiple unique objects\n\
\t                  like cameras and lights. (tip: use the arrow\n\
\t                  keys to cycle through available cameras)\n\
\t-b <backend>      Set the render backend. Valid modes are:\n\
\t                  %s\n\
\t-f <frontend>     Set the frontend. Valid modes are:\n\
\t                  %s\n\
\n\
If an input file is specified, the program will run in direct rendering mode,\n\
and will render the scene in an editor window.\n\
"
# endif
#else
# define CLI_USAGE "Usage: %s [-h] [-v] [-V] <input_file.rt>\n\
\n\
\t-h                Display this help message.\n\
\t-v                Display the version of the program.\n\
\t-V                Increase the verbosity of the program,\n\
\t                  can be used multiple times (max 3).\n\
\n\
When an input file is specified, the program will run in direct rendering mode,\n\
and will render the scene in an editor window.\n\
"
#endif // FEAT_CLI_FLAGS

bool	rt_cli_provide_backends(char *string, size_t size, const char *match)
{
	t_rt_backend_provider	*g_backend_providers;
	size_t					i;
	bool					found;

	i = 0;
	found = false;
	g_backend_providers = rt_backend_providers();
	while (g_backend_providers[i].name)
	{
		if (match && !ft_strcmp(g_backend_providers[i].name, match))
			found = true;
		ft_strlcat(string, g_backend_providers[i].name, size);
		if (g_backend_providers[i + 1].name)
			ft_strlcat(string, ", ", size);
		i++;
	}
	return (found);
}

bool	rt_cli_provide_frontends(char *string, size_t size, const char *match)
{
	t_rt_frontend_provider	*g_frontend_providers;
	size_t					i;
	bool					found;

	i = 0;
	found = false;
	g_frontend_providers = rt_frontend_providers();
	while (g_frontend_providers[i].name)
	{
		if (match && !ft_strcmp(g_frontend_providers[i].name, match))
			found = true;
		ft_strlcat(string, g_frontend_providers[i].name, size);
		if (g_frontend_providers[i + 1].name)
			ft_strlcat(string, ", ", size);
		i++;
	}
	return (found);
}

void	rt_cli_opt_help(t_rt *rt)
{
	char	backends[2048];
	char	frontends[2048];

	ft_memset(backends, 0, sizeof(backends));
	ft_memset(frontends, 0, sizeof(frontends));
	rt_cli_provide_backends(backends, sizeof(backends), NULL);
	rt_cli_provide_frontends(frontends, sizeof(frontends), NULL);
	ft_dprintf(STDERR_FILENO, CLI_USAGE, rt->executable, backends, frontends);
}
