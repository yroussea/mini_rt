/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_texture_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:27:26 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 17:37:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/texture.h>
#include <stddef.h>

void	toc_texture_fill(t_toc_texture *texture, t_toc_color color)
{
	int	i;

	i = 0;
	while (i < texture->size.x * texture->size.y)
	{
		texture->data[i] = color;
		i++;
	}
}
