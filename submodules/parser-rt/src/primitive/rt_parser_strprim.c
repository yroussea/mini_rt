/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_strprim.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 04:16:11 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/03 04:16:50 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive.h>

const char	*rt_parser_strprim(enum e_rt_primitive prim)
{
	static const char	*prims[] = {
	[RT_PRIM_COORDINATES] = "coordinates",
	[RT_PRIM_ROTATION] = "rotation",
	[RT_PRIM_COLOR] = "color",
	[RT_PRIM_INT] = "int",
	[RT_PRIM_UINT] = "unsigned int",
	[RT_PRIM_DOUBLE] = "double",
	[RT_PRIM_ANGLE] = "angle",
	};

	if (prim < 0 || prim >= _RT_PRIM_SIZE)
		return ("unknown");
	return (prims[prim]);
}
