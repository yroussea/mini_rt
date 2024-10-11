/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parse_err_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 23:42:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/10 23:43:53 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/parser/error.h>

__attribute__((always_inline))
t_rt_parse_error	rt_parse_err_file(t_rt_parser_file_context context)
{
	t_rt_parse_error	error;

	ft_memset(&error, 0, sizeof(t_rt_parse_error));
	error.type = RT_PARSE_ERR_FILE;
	error.file_context = context;
	return (error);
}
