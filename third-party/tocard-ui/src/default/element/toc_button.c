/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toc_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:56:03 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:00:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tocard/ui.h>

static void	render(
	t_toc_elem *elem,
	t_toc_vec2i mouse_pos
) {
	t_toc_color			color;

	if (toc_elem_is_hovered(elem, mouse_pos))
		color = toc_color(0xFFFF0000);
	else
		color = toc_color(0xCC000011);
	toc_draw_rect(elem->screen, toc_vec2i(elem->x, elem->y), toc_vec2i(
			elem->x + elem->width, elem->y + elem->height), color);
}

static void	mouse(
	t_toc_elem *elem,
	t_toc_vec2i mouse_pos,
	int button,
	int action
) {
	const bool	hovered = toc_elem_is_hovered(elem, mouse_pos);

	if (!hovered)
		elem->last_click = false;
	if (button == 1)
	{
		if (action == 1 && hovered)
			elem->last_click = true;
		else if (action == 0 && elem->last_click)
		{
			elem->last_click = false;
			if (elem->screen->def.action)
				elem->screen->def.action(elem->screen, elem);
		}
	}
}

static t_toc_button_data	*toc_button_data(const char *text)
{
	t_toc_button_data	*data;

	data = malloc(sizeof(t_toc_button_data));
	if (!data)
		return (NULL);
	data->text = text;
	return (data);
}

static void	toc_button_destroy(t_toc_elem *elem)
{
	if (elem->data)
		free(elem->data);
}

t_toc_elem	*toc_button(
	int id,
	t_toc_vec2i pos,
	t_toc_vec2i size,
	const char *text
) {
	static t_toc_elem_def	def = {0};
	t_toc_elem				*elem;
	t_toc_button_data		*data;

	def.destroy = toc_button_destroy;
	def.render = render;
	def.mouse = mouse;
	data = toc_button_data(text);
	if (!data)
		return (NULL);
	elem = toc_elem_create(id, def);
	if (!elem)
		free(data);
	if (!elem)
		return (NULL);
	elem->data = data;
	elem->x = pos.x;
	elem->y = pos.y;
	elem->width = size.x;
	elem->height = size.y;
	return (elem);
}
