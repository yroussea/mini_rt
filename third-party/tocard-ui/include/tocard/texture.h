/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:07:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 17:47:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H
# undef TEXTURE_H
# ifndef __TOCARD_TEXTURE_H__
#  define __TOCARD_TEXTURE_H__

#  include <tocard/util.h>

typedef void	*t_toc_load_fn(void *mlx, char *path, int *width, int *height);

typedef struct s_toc_texture_loader
{
	const char		*ext;
	t_toc_load_fn	*load;
}	t_toc_texture_loader;

typedef struct s_toc_texture
{
	t_toc_vec2i		size;
	t_toc_color		*data;
}	t_toc_texture;

t_toc_texture	*toc_texture_empty(t_toc_vec2i size);
t_toc_texture	*toc_texture_load(void *mlx, const char *path);
void			toc_texture_free(t_toc_texture *texture);

void			toc_texture_fill(t_toc_texture *texture, t_toc_color color);

# endif // __TOCARD_TEXTURE_H__
#endif // TEXTURE_H
