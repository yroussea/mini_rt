/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_default.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:18:29 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:26:22 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/ui.h>
#include <tocard/util.h>

static void	init(t_toc_screen *screen)
{
	const t_toc_vec2i	buttons_size = toc_vec2i(250, 30);
	const int			button1_x = screen->width / 2 - buttons_size.x - 2;
	const int			button2_x = screen->width / 2 + 2;
	const int			button_y = toc_min(screen->height / 2 + 150,
			screen->height - 50);

	toc_screen_add(screen, toc_button(1, toc_vec2i(button1_x, button_y),
			buttons_size, "About"));
	toc_screen_add(screen, toc_button(2, toc_vec2i(button2_x, button_y),
			buttons_size, "Exit"));
}

static bool	render(t_toc_screen *screen, [[maybe_unused]] t_toc_vec2i mouse_pos)
{
	static t_toc_vec2i	origin = {0, 0};
	const t_toc_vec2i	size = toc_vec2i(screen->width, screen->height);
	t_toc_color			color;

	if (screen->window->focused)
		color = toc_color(TOCARD_DEFAULT_BG);
	else
		color = toc_color(TOCARD_DEFAULT_BG_UNFOCUSED);
	toc_draw_rect(screen, origin, size, color);
	return (true);
}

static void	action_performed(
	t_toc_screen *screen,
	t_toc_elem *elem
) {
	t_toc_window	*window;

	if (elem->id == 1)
	{
		window = toc_window_create(screen->window->engine, "About tocard-ui",
				400, 300);
		if (window)
			toc_window_set_screen(window, toc_default_screen_about(), NULL);
	}
	else if (elem->id == 2)
		toc_engine_exit(screen->window->engine);
}

t_toc_screen_def	toc_default_screen(void)
{
	static t_toc_screen_def	def = {0};
	static bool				initialized = false;

	if (!initialized)
	{
		def.id = TOCARD_DEFAULT_SCREEN_ID;
		def.init = init;
		def.render = render;
		def.action = action_performed;
		initialized = true;
	}
	return (def);
}
