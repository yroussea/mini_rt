/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:15:32 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/17 23:48:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <termengine.h>

void	te_str_append(const char *src, char *dst, char **remain)
{
	const char	*tmp;

	tmp = src;
	while (*tmp)
		*dst++ = *tmp++;
	if (remain)
		*remain = (char *)dst;
}

char	*tr_color(uint32_t color)
{
	static char	buffer[TE_BLEN] = {0};
	uint32_t	comp;

	color &= ~(0xFF << 24);
	te_str_append(";000;000;000m", buffer, NULL);
	comp = (color & TE_RGB_RED) >> 14;
	te_str_append(&TE_COLOR_TABLE[comp], &buffer[1], NULL);
	comp = (color & TE_RGB_GREEN) >> 6;
	te_str_append(&TE_COLOR_TABLE[comp], &buffer[5], NULL);
	comp = (color & TE_RGB_BLUE) << 2;
	te_str_append(&TE_COLOR_TABLE[comp], &buffer[9], NULL);
	return (buffer);
}

void	te_str_append_color(uint32_t mode, uint32_t color,
			char *cursor, char **remain)
{
	const char	*prefix;

	prefix = TE_ANSI_RGB_BG;
	if (mode)
		prefix = TE_ANSI_RGB_FG;
	te_str_append(prefix, cursor, &cursor);
	te_str_append(tr_color(color), cursor, &cursor);
	if (remain)
		*remain = cursor;
}
