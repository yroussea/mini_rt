/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:03:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/08 20:41:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math.h>
#include <ft/mem.h>
#include <ft/string.h>
#include <ft/string/parse.h>
#include <rt/app.h>
#include <rt/features.h>
#include <rt/log.h>
#include <rt/render/backend.h>
#include <rt/render/frontend.h>

#define RT_DEFAULT_WIDTH	1280
#define RT_DEFAULT_HEIGHT	720

static const char	*rt_getenv(const char *name, const char **envp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0)
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	rt_flags_init(t_rt *rt, const char **envp)
{
	const char	*env = rt_getenv("RT_VERBOSITY", envp);

	if (env)
		rt->flags.verbosity = ft_max(0, ft_atoi(env));
	rt_trace(rt, "verbosity: %d\n", (int)rt->flags.verbosity);
	rt->flags.mode = RT_MODE_RENDER_LOOP;
	rt->flags.frontend = rt_frontend_providers()[0].name;
	if (!rt->flags.frontend)
	{
		rt_error(rt, "no frontends available, exiting\n");
		return (1);
	}
	rt->flags.backend = rt_backend_providers()[0].name;
	if (!rt->flags.backend)
	{
		rt_error(rt, "no backends available, exiting\n");
		return (1);
	}
	return (0);
}

int	rt_init(
	t_rt *rt,
	__attribute__((unused)) int argc,
	__attribute__((unused)) const char **argv,
	const char **envp
) {
	ft_memset(rt, 0, sizeof(t_rt));
	rt->executable = argv[0];
	rt->name = RT_DEFAULT_NAME;
	rt->width = RT_DEFAULT_WIDTH;
	rt->height = RT_DEFAULT_HEIGHT;
	return (rt_flags_init(rt, envp));
}
