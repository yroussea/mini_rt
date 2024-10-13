/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:46:25 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:56:41 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/math/vector.h"
#include <ft/mem.h>
#include "mlx.h"
#include <mlx_manage.h>

void	mm_getmdata(t_mdata **var)
{
	static t_mdata	*mdata;

	if (var && *var)
		mdata = *var;
	else
		*var = mdata;
}

void	mm_init(
	t_mdata *mdata,
	void destoy_fnct(void),
	void loop_fnct(t_mdata *),
	t_loop_param param_fnct
)
{
	void	*mlx;
	void	*wind;
	void	*img;

	mlx = mlx_init();
	if (!mlx)
		return ;
	wind = mlx_new_window(mlx, WIDTH, HEIGHT, "mrt");
	if (wind)
	{
		img = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (img)
		{
			*mdata = (t_mdata){.mlx = mlx, .wind = wind, .img = img,
				.destroy_fnct = destoy_fnct, .pixelisation = 1,
				.loop_fnct = loop_fnct, .param_fnct = param_fnct};
			mm_getmdata(&mdata);
			return ;
		}
		mlx_destroy_window(mlx, wind);
	}
	mlx_destroy_display(mlx);
}
