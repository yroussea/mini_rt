/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_color_rgba.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:19 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/24 16:15:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/util.h>

t_toc_color	toc_color_rgba(unsigned char r, unsigned char g, unsigned char b,
				unsigned char a)
{
	return ((t_toc_color){.r = r, .g = g, .b = b, .a = a});
}
