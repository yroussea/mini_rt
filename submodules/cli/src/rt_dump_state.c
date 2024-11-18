/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_dump_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:58:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 20:59:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/cli.h>
#include <rt/log.h>

void	rt_dump_state(const t_rt *rt)
{
	rt_debug(rt, "launching rt in mode %d\n", rt->flags.mode);
	rt_debug(rt, "input file is '%s'\n", rt->flags.filepath);
	if (rt->flags.mode == RT_MODE_RENDER_ONCE)
		rt_debug(rt, "output file is '%s'\n", rt->flags.output);
	rt_debug(rt, "frontend is '%s'\n", rt->flags.frontend);
	rt_debug(rt, "backend is '%s'\n", rt->flags.backend);
}
