/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:12:38 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 05:53:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/app.h>
#include <rt/log.h>
#include <stdlib.h>

void	rt_exit(t_rt *rt, int status)
{
	rt_error(rt, "exiting with status %d", status);
	rt_destroy(rt);
	exit(status);
}
