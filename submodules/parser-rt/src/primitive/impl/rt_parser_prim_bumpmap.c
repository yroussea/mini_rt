/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_bumpmap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:36:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 01:37:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <rt/log.h>
#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
#include <rt/util.h>

static void	*rt_parser_prim_bumpmap_img(
	void *mlx,
	char *slice,
	int *width,
	int *height
) {
	const char	*ext = ft_strrchr(slice, '.');

	if (!ext)
		rt_debug(NULL, "no extension found in '%s', trying 'png'...\n", slice);
	if (!ext)
		ext = ".png";
	ext++;
	if (!*ext)
		rt_debug(NULL, "no extension found in '%s', trying 'png'...\n", slice);
	if (!*ext)
		ext = "png";
	if (ft_strcmp(ext, "png") == 0)
		return (mlx_png_file_to_image(mlx, slice, width, height));
	else if (ft_strcmp(ext, "jpg") == 0)
		return (mlx_jpg_file_to_image(mlx, slice, width, height));
	else if (ft_strcmp(ext, "bmp") == 0)
		return (mlx_bmp_file_to_image(mlx, slice, width, height));
	else
	{
		rt_debug(NULL, "unknown extension '%s', trying 'png'...\n", ext);
		return (mlx_png_file_to_image(mlx, slice, width, height));
	}
	return (NULL);
}

static RESULT	rt_parser_prim_bumpmap_load(
	void *mlx,
	void *mlx_img,
	t_vec2i img_size,
	void *memory
) {
	t_vec3d	*target;
	t_vec2i	pos;
	int		data;

	target = rt_malloc_aligned(img_size.x * img_size.y * sizeof(t_vec3d), 32);
	if (!target)
		return (ERRS(PARSE_ERR_ALLOC, "failed to allocate bumpmaps"));
	*((t_vec3d **)memory) = target;
	pos = (t_vec2i){0, 0};
	while (pos.x < img_size.x)
	{
		while (pos.y < img_size.y)
		{
			data = mlx_get_image_pixel(mlx, mlx_img, pos.x, pos.y);
			target[pos.x + pos.y * (img_size.x)] = (t_vec3d){
				.x = (data >> 16) & 0xFF,
				.y = (data >> 8) & 0xFF,
				.z = data & 0xFF
			};
			pos.y++;
		}
		pos.y = 0;
		pos.x++;
	}
	return (OK());
}

RESULT	rt_parser_prim_bumpmap(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	void	*mlx;
	void	*mlx_img;
	t_vec2i	img_size;

	mlx = mlx_init();
	if (!mlx)
		return (ERRS(PARSE_ERR_ALLOC, "failed to initialize sub-mlx"));
	mlx_img = rt_parser_prim_bumpmap_img(mlx, (char *)slice, &img_size.x,
			&img_size.y);
	if (mlx_img && (!img_size.x || !img_size.y))
		mlx_destroy_image(mlx, mlx_img);
	if (!mlx_img || !img_size.x || !img_size.y)
		mlx_destroy_display(mlx);
	if (!mlx_img || !img_size.x || !img_size.y)
		return (ERRS(PARSE_ERR_ALLOC, "failed to load image"));
	rt_parser_prim_bumpmap_load(mlx, mlx_img, img_size, memory
		+ offsetof(t_rt_material, bump));
	*((t_vec2i *)(memory + offsetof(t_rt_material, bump) + sizeof(t_vec3d *)))
		= (t_vec2i){img_size.x * img_size.y};
	*size = 1;
	mlx_destroy_image(mlx, mlx_img);
	mlx_destroy_display(mlx);
	return (OK());
}
