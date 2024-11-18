/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 00:49:19 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/17 23:47:42 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termengine.h>

void	te_terminal_hook(t_terminal *t, enum e_hook_types type,
			t_hook_func func, void *param)
{
	t->hook_table.hooks[type] = func;
	t->hook_table.params[type] = param;
}
