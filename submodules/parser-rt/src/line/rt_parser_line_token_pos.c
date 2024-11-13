/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_line_token_pos.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 04:25:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/13 06:10:32 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/string.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>

/**
 * @brief Finds the position of a token in a line.
 *
 * @param line The line to search in.
 * @param tokens An array of tokens to search for.
 * @param itoken The token index to search for.
 *
 * @return The position of the token in the line.
 */
size_t	rt_parser_line_token_pos(const char *line, char **tokens, size_t itoken)
{
	const char	*tmp;
	size_t		n;

	n = itoken + 1;
	tmp = line;
	while (tmp && n > 0)
	{
		tmp = ft_strstr(tmp, tokens[itoken]);
		n--;
		if (n != 0)
			tmp += ft_strlen(tokens[itoken]);
	}
	return (tmp - line);
}
