/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_token_pos.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:25:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:34:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

/**
 * @brief Finds the position of a token in a line.
 *
 * @param line The line to search in.
 * @param itoken The token index to search for.
 *
 * @return The position of the token in the line.
 */
size_t	rt_parser_line_token_pos(const char *line, size_t itoken)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)line;
	i = 0;
	while (tmp[i])
	{
		while (tmp[i] && tmp[i] == ' ')
			i++;
		if (tmp[i] && tmp[i] != ' ')
		{
			if (itoken > 0)
				itoken--;
			else
				return (i);
		}
		while (tmp[i] && tmp[i] != ' ')
			i++;
	}
	return (i);
}
