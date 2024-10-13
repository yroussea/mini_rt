/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manage.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 21:57:03 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 13:49:16 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_MANAGE_H
# define MLX_MANAGE_H

# include "object.h"
# include <mlx.h>
# include <sys/types.h>

# define WIDTH 960
# define HEIGHT 540
# define NB_EVENT 10

typedef enum e_keycode
{
	ESCAPE = 41,
}			t_keycode;

typedef struct s_loop_param
{
	void	(*all_ray)(t_objs *, void f(t_objs *, t_ray, int, int), ushort, ushort);
	void	(*one_ray)(t_objs *, t_ray , int , int );
}			t_loop_param;

typedef struct s_event
{
	mlx_event_type	event_type;
	t_keycode		keycode;
	void			(*f)(void *);
}					t_event;

typedef struct s_mdata
{
	void			*mlx;
	void			*wind;
	void			*img;
	void			(*destroy_fnct)(void);
	void			(*loop_fnct)(struct s_mdata *data);
	t_loop_param	param_fnct;
	uint			pixelisation;
	t_vec3d			colors[WIDTH];
	t_event			event[NB_EVENT];
}					t_mdata;

/*
 * USER PART
*/
void	mm_init(
			t_mdata *mdata, void destoy_fnct(void),
			void loop_fnct(t_mdata *), t_loop_param param_fnct);
void	mm_add_event(t_mdata *mdata, t_event event);
void	mm_loop(void *var);
void	mm_draw_pixel(uint x, t_vec3d colors);
void	mm_draw_ligne(uint y);
void	mm_draw_image(t_mdata *mdata);

/*
 * BACK STAGE
*/
void	mm_event(t_mdata *mdata);
void	mm_getmdata(t_mdata **var);
void	mm_kill(void *var);



#endif
