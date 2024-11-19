/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_engine_hook_pre.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 01:48:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 02:37:09 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/engine.h>

void	toc_engine_hook_pre(t_toc_engine *engine, t_toc_engine_hook *hook)
{
	if (!engine)
		return ;
	engine->_hook_pre = hook;
}
