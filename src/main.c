/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/29 23:41:58 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <threading.h>
#include <parsing.h>
#include <ray.h>

int	main(int ac, char **av)
{
	int			**colors = NULL;
	t_light		*light = NULL;
	t_objs		*objs = NULL;

	if (!ac)
		return (1);
	parsing(av[1]);
	get_colors(&colors);
	verify(colors, light, objs, COLOR);
	get_objs(&objs);
	verify(colors, light, objs, COLOR | OBJS);
	get_lights(&light);
	verify(colors, light, objs, COLOR | OBJS | LIGHT);
	init_mlx(&genering_image);
	free_scene_data(colors, light, objs, ALL);
}

