/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_screen_about.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:42:52 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 19:37:40 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/ui.h>
#include <stdio.h>

static void	init(t_toc_screen *screen)
{
	const t_toc_vec2i	button_size = toc_vec2i(150, 25);
	const int			button_x = screen->width / 2 - button_size.x / 2;
	const int			button_y = screen->height - 50;

	toc_screen_add(screen, toc_button(1, toc_vec2i(button_x, button_y),
			button_size, "Ok"));
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
	if (elem->id == 1)
		toc_window_close(screen->window);
}

t_toc_screen_def	toc_default_screen_about(void)
{
	static t_toc_screen_def	def = {0};
	static bool				initialized = false;

	if (!initialized)
	{
		def.id = TOCARD_ABOUT_SCREEN_ID;
		def.init = init;
		def.render = render;
		def.action = action_performed;
		initialized = true;
	}
	return (def);
}
