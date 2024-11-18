/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_prim_bumpmap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 16:36:25 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/19 00:55:20 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt/parser/primitive/strtod.h>
#define __RT_PARSER_INTERNAL__
#include <rt/parser.h>
# include <stdio.h>
#include <mlx.h>

RESULT	rt_parser_prim_bumpmap(
	__attribute__((unused)) t_rt_parser *parser,
	const char *slice,
	void *memory,
	size_t *size
) {
	void	*mlx;
	void	*mlx_img;
	size_t	width;
	size_t	height;

	mlx = mlx_init();
	if (!mlx)
		return (ERRS(PARSE_ERR_ALLOC, "failed to initialize sub-mlx"));
	mlx_img = rt_parser_prim_bumpmap_img(mlx, slice, &width, &height);
	if (!mlx_img)
		return (ERRS(PARSE_ERR_ALLOC, "failed to load image"));
	mlx_destroy_image(mlx_img);
	mlx_destroy(mlx);
	return (OK());
}
