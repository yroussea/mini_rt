/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_ctor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 23:52:02 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 21:01:29 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/devreload.h>

#ifndef RT_DEVRELOAD_SUBMODULES_PATH
# error "RT_DEVRELOAD_SUBMODULES_PATH is not defined"
#endif

static void	rt_devrl_load(const char *path, const char *backends,
				t_devrl_load_fn load_fn)
{
	char	*next;

	while (backends)
	{
		next = ft_strchr(backends, ' ');
		if (!next)
			load_fn(path, backends);
		else
		{
			*next = 0;
			load_fn(path, backends);
			backends = next + 1;
			continue ;
		}
		break ;
	}
}

__attribute__((constructor))
void	rt_devrl_ctor(void)
{
	char	frontends[4096];
	char	backends[4096];

	ft_memset(frontends, 0, sizeof(frontends));
	ft_memset(backends, 0, sizeof(backends));
	ft_strlcpy(frontends, RT_DEVRELOAD_FRONTENDS, sizeof(frontends));
	ft_strlcpy(backends, RT_DEVRELOAD_BACKENDS, sizeof(backends));
	RT_DEBUG("submodules path: %s\n", RT_DEVRELOAD_SUBMODULES_PATH);
	RT_DEBUG("backends: %s\n", RT_DEVRELOAD_BACKENDS);
	RT_DEBUG("frontends: %s\n", RT_DEVRELOAD_FRONTENDS);
	rt_devrl_load(RT_DEVRELOAD_SUBMODULES_PATH, frontends,
		&rt_devrl_load_frontend);
	rt_devrl_load(RT_DEVRELOAD_SUBMODULES_PATH, backends,
		&rt_devrl_load_backend);
}
