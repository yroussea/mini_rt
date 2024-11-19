/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_texture_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:37:10 by kiroussa          #+#    #+#             */
/*   Updated: 2024/05/24 19:43:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/texture.h>
#include <stdlib.h>

void	toc_texture_free(t_toc_texture *tex)
{
	if (!tex)
		return ;
	if (tex->data)
		free(tex->data);
	free(tex);
}
