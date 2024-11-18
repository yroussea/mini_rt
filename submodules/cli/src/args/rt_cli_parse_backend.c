/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_parse_backend.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:12:14 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:14:01 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/log.h>
#include <rt/cli.h>

bool	rt_cli_provide_backends(char *string, size_t size, const char *match);

int	rt_cli_parse_backend(t_rt *rt, char *backend)
{
	char	backend_list[2048];
	bool	found;

	ft_memset(backend_list, 0, sizeof(backend_list));
	found = rt_cli_provide_backends(backend_list, sizeof(backend_list),
			backend);
	if (found)
	{
		rt_debug(rt, "cli: setting 'backend' to %s\n", backend);
		rt->flags.backend = backend;
		return (CLI_PASS);
	}
	rt_error(rt, "invalid backend: %s\nvalid backends are: %s\n",
		backend, backend_list);
	return (CLI_EXIT_FAILURE);
}
