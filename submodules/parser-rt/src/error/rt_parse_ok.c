/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_ok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:34:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/12 02:43:48 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser/error.h>
#include <stdbool.h>

__attribute__((always_inline))
t_rt_parse_error	rt_parse_ok(void)
{
	static t_rt_parse_error	ok = {0};
	static bool				init = false;

	if (!init)
	{
		ft_memset(&ok, 0, sizeof(ok));
		ok.type = PARSE_ERR_OK;
		init = true;
	}
	return (ok);
}
