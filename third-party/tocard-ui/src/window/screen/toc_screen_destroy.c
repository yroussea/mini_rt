/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:17:57 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/12 16:01:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/window.h>
#include <stdlib.h>

void	toc_screen_destroy(t_toc_screen *screen)
{
	if (!screen || !screen->def.id)
		return ;
	if (screen->def.destroy)
		screen->def.destroy(screen);
	if (screen->image)
		mlx_destroy_image(screen->window->engine->mlx, screen->image);
	toc_list_clear(&screen->elements, (t_destroy_fn *) &toc_elem_destroy);
}
