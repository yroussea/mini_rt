/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_color_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:00:35 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/24 16:15:46 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/util.h>

t_toc_color	toc_color_rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((t_toc_color){.r = r, .g = g, .b = b, .a = 255});
}
