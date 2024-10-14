/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_errd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:34:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/12 02:43:35 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser/error.h>

__attribute__((always_inline))
t_rt_parse_error	rt_parse_errd(enum e_rt_parse_error type, void *data)
{
	t_rt_parse_error	err;

	ft_memset(&err, 0, sizeof(err));
	err.type = type;
	err.data = data;
	return (err);
}
