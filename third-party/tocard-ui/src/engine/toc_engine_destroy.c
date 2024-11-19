/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_engine_destroy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 01:41:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 01:52:02 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/engine.h>
#include <stdlib.h>

void	toc_engine_destroy(t_toc_engine *engine)
{
	if (engine->mlx)
		mlx_destroy_display(engine->mlx);
	if (engine->windows)
		toc_list_clear(&engine->windows, free);
	if (engine->fonts)
		toc_list_clear(&engine->fonts, free);
	free(engine);
}
