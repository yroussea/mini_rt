/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parse_frontend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:10:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:14:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#include <rt/cli.h>

bool	rt_cli_provide_frontends(char *string, size_t size, const char *match);

int	rt_cli_parse_frontend(t_rt *rt, char *frontend)
{
	char	frontend_list[2048];
	bool	found;

	ft_memset(frontend_list, 0, sizeof(frontend_list));
	found = rt_cli_provide_frontends(frontend_list, sizeof(frontend_list),
			frontend);
	if (found)
	{
		rt_debug(rt, "cli: setting 'frontend' to %s\n", frontend);
		rt->flags.frontend = frontend;
		return (CLI_PASS);
	}
	rt_error(rt, "invalid frontend: %s\nvalid frontends are: %s\n",
		frontend, frontend_list);
	return (CLI_EXIT_FAILURE);
}
