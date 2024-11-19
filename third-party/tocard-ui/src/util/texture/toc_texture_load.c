/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_texture_load.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:22:01 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 18:04:59 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <tocard/texture.h>

static char	*toc_strrchr(const char *s, int c)
{
	size_t	len;

	if (s)
	{
		len = toc_strlen(s);
		if ((unsigned char)c == 0)
			return ((char *)s + len);
		while (len--)
			if (s[len] == (unsigned char)c)
				return ((char *)s + len);
	}
	return (NULL);
}

static t_toc_load_fn	*toc_image_load_function(const char *path)
{
	static t_toc_texture_loader	loaders[] = {
	{"png", mlx_png_file_to_image},
	{"jpg", mlx_jpg_file_to_image},
	{"jpeg", mlx_jpg_file_to_image},
	{"bmp", mlx_bmp_file_to_image},
	};
	char						*ext;
	size_t						i;

	ext = toc_strrchr(path, '.');
	if (!ext || !*ext || !*(ext + 1))
		return (loaders[0].load);
	i = 0;
	while (i < sizeof(loaders) / sizeof(*loaders))
	{
		if (!toc_strcmp_ignorecase(ext + 1, loaders[i].ext))
			return (loaders[i].load);
		i++;
	}
	return (loaders[0].load);
}

static void	toc_fill_from_image(t_toc_texture *tex, t_toc_vec2i size,
				void *mlx, void *img)
{
	int	i;

	i = 0;
	tex->size = size;
	while (i < size.x * size.y)
	{
		tex->data[i] = toc_color(mlx_get_image_pixel(mlx, img, i % size.x,
					i / size.x));
		i++;
	}
}

t_toc_texture	*toc_texture_load(void *mlx, const char *path)
{
	t_toc_texture	*tex;
	void			*img;
	t_toc_vec2i		size;

	tex = NULL;
	img = toc_image_load_function(path)(mlx, (char *)path, &size.x, &size.y);
	if (img && size.x && size.y)
	{
		tex = toc_texture_empty(size);
		if (tex)
			toc_fill_from_image(tex, size, mlx, img);
	}
	if (img)
		mlx_destroy_image(mlx, img);
	return (tex);
}
