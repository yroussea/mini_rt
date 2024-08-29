/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:48:50 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/29 22:50:30 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <threading.h>
#include <ray.h>

int	main()
{
	int			**colors = NULL;
	t_light		*light = NULL;
	t_objs		*objs = NULL;

	get_colors(&colors);
	verify(colors, light, objs, COLOR);
	get_objs(&objs);
	verify(colors, light, objs, COLOR | OBJS);
	get_lights(&light);
	verify(colors, light, objs, COLOR | OBJS | LIGHT);
	init_mlx(&genering_image);
	free_scene_data(colors, light, objs, ALL);
}

