/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:08:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/15 00:34:23 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/render/backend.h>
#include <rt/render/frontend/macrolibx.h>
#include <rt/log.h>
#include <tocard/screen.h>
#include <tocard/draw.h>
#include <SDL2/SDL_scancode.h>

static bool	rt_screen_main_render(t_toc_screen *self, t_toc_vec2i mouse)
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
	(void) mouse;
	return (true);
}

static bool	rt_screen_main_key(t_toc_screen *screen, int key, int action,
				int last)
{
	t_rt_frontend		*frontend;

	(void) screen;
	printf("rt screen: key %d action %d last %d\n", key, action, last);
	frontend = (t_rt_frontend *)screen->data;
	if (action && !last && key == SDL_SCANCODE_R
		&& screen->window->keymap[SDL_SCANCODE_LALT])
	{
		printf("rt screen: reloading backend\n");
		frontend->rt->backend->destroy(frontend->rt->backend);
		frontend->rt->backend = rt_backend_provider_find("dummy")->fn(
			frontend->rt, rt_backend_provider_find("dummy")->name, frontend->width, frontend->height);
		frontend->rt->backend->init(frontend->rt->backend);
		printf("rt screen: backend reloaded\n");
	}
	return (true);
}

t_toc_screen_def	rt_screen_main(void)
{
	static t_toc_screen_def	screen;

	ft_memset(&screen, 0, sizeof(t_toc_screen_def));
	screen.id = "rt:main";
	screen.render = rt_screen_main_render;
	screen.key = rt_screen_main_key;
	return (screen);
}
