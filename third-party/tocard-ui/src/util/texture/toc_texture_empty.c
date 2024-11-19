/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_texture_empty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:17:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 18:05:38 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/texture.h>
#include <stdlib.h>

t_toc_texture	*toc_texture_empty(t_toc_vec2i size)
{
	static t_toc_color	empty_color = {0};
	t_toc_texture		*tex;

	tex = malloc(sizeof(t_toc_texture));
	if (!tex)
		return (NULL);
	tex->size = size;
	tex->data = malloc(size.x * size.y * sizeof(t_toc_color));
	if (!tex->data)
	{
		free(tex);
		return (NULL);
	}
	toc_texture_fill(tex, empty_color);
	return (tex);
}
