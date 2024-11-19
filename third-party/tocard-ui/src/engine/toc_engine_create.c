/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_engine_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:30:36 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/11 02:37:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/engine.h>
#include <stdlib.h>

t_toc_engine	*toc_engine_create(void)
{
	t_toc_engine	*engine;

	engine = malloc(sizeof(t_toc_engine));
	if (!engine)
		return (NULL);
	engine->mlx = mlx_init();
	if (!engine->mlx)
	{
		free(engine);
		return (NULL);
	}
	engine->_hook_pre = NULL;
	engine->_hook_post = NULL;
	engine->windows = NULL;
	engine->fonts = NULL;
	return (engine);
}
