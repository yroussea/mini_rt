/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:08:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 18:25:57 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_DEVMODE
# define RT_DEVMODE 0
#endif // RT_DEVMODE

#include <ft/math/vector.h>
#include <ft/mem.h>
#if RT_DEVMODE
# include <rt/devreload.h>
#endif // RT_DEVMODE
#include <rt/render/backend.h>
#include <rt/render/frontend/macrolibx.h>
#include <rt/log.h>
#include <tocard/screen.h>
#include <tocard/draw.h>
#include <SDL2/SDL_scancode.h>

#if !RT_DEVMODE

void	rt_devrl_check_reload(void *a);

#endif // !RT_DEVMODE

//FIXME: uninitialized value in tocard-ui `t_toc_window#keymap`
static void	rt_screen_main_init(t_toc_screen *self)
{
	ft_memset(self->window->keymap, 0, sizeof(self->window->keymap));
}

static void	rt_pixelate(t_rt_frontend *frontend, t_rt_backend *backend,
				t_color *source, t_color *target)
{
	const t_vec2i			target_size = v2i(frontend->width,
			frontend->height);
	const t_vec2i			source_size = v2i(backend->width, backend->height);
	const t_vec2i			scales = v2i(target_size.x / source_size.x,
			target_size.y / source_size.y);
	t_vec2i					source_pos;
	t_vec2i					pos;

	pos = v2i(0, 0);
	while (pos.y < target_size.y)
	{
		pos.x = 0;
		while (pos.x < target_size.x)
		{
			source_pos = v2i(pos.x / scales.x, pos.y / scales.y);
			target[pos.y * target_size.x + pos.x] = \
				source[source_pos.y * source_size.x + source_pos.x];
			pos.x++;
		}
		pos.y++;
	}
}

static bool	rt_screen_main_render(t_toc_screen *self,
				__attribute__((unused)) t_toc_vec2i mouse)
{
	t_rt_frontend		*frontend;
	t_rt_frontend_mlx	*front;
	t_rt_backend		*backend;
	t_toc_vec2i			pos;

	frontend = (t_rt_frontend *)self->data;
	front = (t_rt_frontend_mlx *)frontend->data;
	if (RT_DEVMODE)
		rt_devrl_check_reload(frontend->rt);
	toc_draw_rect(self, toc_vec2i(0, 0), toc_vec2i(self->width, self->height),
		(t_toc_color){.value = 0xFF000000});
	backend = frontend->rt->backend;
	ft_memcpy(front->buffer, backend->render(backend), self->width * self->height
		   * sizeof(t_color));
	//rt_pixelate(frontend, backend, backend->render(backend), front->buffer);
	pos = toc_vec2i(0, 0);
	while (pos.y < (int)frontend->height)
	{
		pos.x = -1;
		while (++pos.x < (int)frontend->width)
			toc_draw_pixel(self, pos, (t_toc_color){.value
				= front->buffer[pos.y * frontend->width + pos.x].rgba});
		pos.y++;
	}
	return (true);
}

static bool	rt_screen_main_key(t_toc_screen *screen, int key, int action,
				int last)
{
	t_rt_frontend	*frontend;
	bool			ctrl;

	if (!action || last)
		return (true);
	frontend = (t_rt_frontend *)screen->data;
	ctrl = screen->window->keymap[SDL_SCANCODE_LCTRL];
	if (ctrl && key == SDL_SCANCODE_I)
		rt_resize(frontend->rt, screen->width - 80, screen->height - 80);
	if (ctrl && key == SDL_SCANCODE_O)
		rt_resize(frontend->rt, screen->width + 80, screen->height + 80);
	return (true);
}

t_toc_screen_def	rt_screen_main(void)
{
	static t_toc_screen_def	screen;

	ft_memset(&screen, 0, sizeof(t_toc_screen_def));
	screen.id = "rt:main";
	screen.init = rt_screen_main_init;
	screen.render = rt_screen_main_render;
	screen.key = rt_screen_main_key;
	return (screen);
}
