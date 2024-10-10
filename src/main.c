/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/10 20:27:08 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <ray.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int			**colors = NULL;
	t_objs		*objs = NULL;

	if (!ac)
		return (1);
	parsing(av[1]);
	get_colors(&colors);
	verify(colors, objs, COLOR);
	get_objs(&objs);
	verify(colors, objs, COLOR | OBJS);
	init_mlx(&genering_image);
	free_scene_data(colors, objs, ALL);
}

