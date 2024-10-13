/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:03:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 04:14:12 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/app.h>
#include <rt/features.h>

int	rt_init(
	t_rt *rt,
	__attribute__((unused)) int argc,
	__attribute__((unused)) char **argv
) {
	ft_memset(rt, 0, sizeof(t_rt));
	rt->executable = argv[0];
	rt->name = RT_DEFAULT_NAME;
	return (0);
}
