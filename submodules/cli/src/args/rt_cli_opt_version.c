/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_cli_opt_version.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:11:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 04:13:30 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/print.h>
#include <rt/cli.h>

void	rt_cli_opt_version(t_rt *rt)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", rt->name, RT_VERSION);
}
