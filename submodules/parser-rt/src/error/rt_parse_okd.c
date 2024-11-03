/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_okd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:18:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 04:18:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/error.h>

t_rt_parse_error	rt_parse_okd(void *data)
{
	t_rt_parse_error	err;

	err.type = PARSE_ERR_OK;
	err.data = data;
	return (err);
}
