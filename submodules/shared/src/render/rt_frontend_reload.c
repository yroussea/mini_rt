/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_frontend_reload.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:11:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 05:22:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/render/frontend.h>

void	rt_frontend_reload(t_rt *rt)
{
	rt_frontend_switch(rt, rt->frontend->name);
}
