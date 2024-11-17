/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:10:00 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 16:23:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H
# undef COLOR_H
# ifndef __RT_COLOR_H__
#  define __RT_COLOR_H__

#  include <stdint.h>

// Note: As we are on x86, no need to check for endianness
// See: https://stackoverflow.com/a/64390149
typedef union u_color
{
	uint32_t	rgba;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}	t_color;

# endif // __RT_COLOR_H__
#endif // COLOR_H
