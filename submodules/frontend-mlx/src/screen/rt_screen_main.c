/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:08:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 18:22:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend.h>
#include <rt/render/frontend/macrolibx.h>
#include <rt/log.h>
#include <tocard/screen.h>
#include <tocard/draw.h>
#include <SDL2/SDL_scancode.h>

static void	rt_screen_main_init(t_toc_screen *self)
{
	ft_memset(self->window->keymap, 0, sizeof(self->window->keymap));
}

static bool	rt_screen_main_render(t_toc_screen *self,
				__attribute__((unused)) t_toc_vec2i mouse)
{
	t_rt_frontend		*frontend;
	t_color				*buffer;
	size_t				x;
	size_t				y;

	frontend = (t_rt_frontend *)self->data;
	buffer = frontend->rt->backend->render(frontend->rt->backend);
	y = 0;
	while (y < frontend->height)
	{
		x = 0;
		while (x < frontend->width)
		{
			toc_draw_pixel(self, (t_toc_vec2i){x, y},
				(t_toc_color){.value = buffer[y * frontend->width + x].rgba});
			x++;
		}
		y++;
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
	if (ctrl && key == SDL_SCANCODE_R)
		rt_backend_reload(frontend->rt);
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
