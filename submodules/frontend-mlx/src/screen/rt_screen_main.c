/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:08:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 23:14:16 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/math/vector.h>
#include <ft/mem.h>
#include <rt/render/backend.h>
#include <rt/render/frontend/macrolibx.h>
#include <rt/log.h>
#include <tocard/screen.h>
#include <tocard/draw.h>
#include <SDL2/SDL_scancode.h>

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

static void	rt_screen_main_update(t_toc_screen *self)
{
	const char			*keymap = (char *)self->window->keymap;
	const t_rt_frontend	*frontend = (t_rt_frontend *)self->data;
	const double		speed = 0.1 + keymap[SDL_SCANCODE_LCTRL] * 2;

	if (keymap[SDL_SCANCODE_Q])
		rt_rotate_camera(frontend->rt, 0.15, 0);
	if (keymap[SDL_SCANCODE_E])
		rt_rotate_camera(frontend->rt, -0.15, 0);
	if (keymap[SDL_SCANCODE_R])
		rt_rotate_camera(frontend->rt, 0, 0.15);
	if (keymap[SDL_SCANCODE_F])
		rt_rotate_camera(frontend->rt, 0, -0.15);
	if (keymap[SDL_SCANCODE_W])
		rt_move_camera(frontend->rt, v3d(0, 0, 1 + speed));
	if (keymap[SDL_SCANCODE_S])
		rt_move_camera(frontend->rt, v3d(0, 0, -(1 + speed)));
	if (keymap[SDL_SCANCODE_A])
		rt_move_camera(frontend->rt, v3d(-(1 + speed), 0, 0));
	if (keymap[SDL_SCANCODE_D])
		rt_move_camera(frontend->rt, v3d(1 + speed, 0, 0));
	if (keymap[SDL_SCANCODE_SPACE])
		rt_move_camera(frontend->rt, v3d(0, 1 + speed, 0));
	if (keymap[SDL_SCANCODE_LSHIFT])
		rt_move_camera(frontend->rt, v3d(0, -(1 + speed), 0));
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
	rt_update(frontend->rt);
	rt_screen_main_update(self);
	toc_draw_rect(self, toc_vec2i(0, 0), toc_vec2i(self->width, self->height),
		(t_toc_color){.value = 0xFF000000});
	backend = frontend->rt->backend;
	rt_pixelate(frontend, backend, backend->render(backend), front->buffer);
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

	if (!action || last)
		return (true);
	frontend = (t_rt_frontend *)screen->data;
	if (key == SDL_SCANCODE_ESCAPE)
		toc_engine_exit(screen->window->engine);
	else if (key == SDL_SCANCODE_LEFT)
		rt_switch_camera_left(frontend->rt, frontend->rt->backend);
	else if (key == SDL_SCANCODE_RIGHT)
		rt_switch_camera_right(frontend->rt, frontend->rt->backend);
	else if (key == SDL_SCANCODE_KP_PLUS)
		rt_pixelisation_upper(frontend->rt);
	else if (key == SDL_SCANCODE_KP_MINUS)
		rt_pixelisation_lower(frontend->rt);
	else
		return (true);
	return (false);
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
