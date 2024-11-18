/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:26:53 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/17 23:57:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <termengine.h>
#include <unistd.h>

uint32_t	te_set_mode(uint32_t mode);
void		te_terminal_get_size(uint32_t *row, uint32_t *col);

t_terminal	*te_init(void)
{
	t_terminal	*t;

	t = malloc(sizeof(t_terminal));
	if (t)
	{
		cm_memset(t, 0, sizeof(t_terminal));
		te_terminal_get_size(&t->row, &t->col);
		t->screen = te_screen_init(t);
		t->back = te_screen_init(t);
		te_set_mode(TE_MODE_RENDER);
		te_ansi(TE_ANSI_CLEAR TE_ANSI_CURSOR_OFF);
		t->images = cm_chunk_init(sizeof(t_te_img));
		if (!t->screen || !t->back || !t->images)
		{
			te_destroy(t);
			return (NULL);
		}
		t->active = 1;
	}
	return (t);
}

void	te_destroy(t_terminal *t)
{
	t_te_img	*tmp;
	t_cm_chunk	*ctmp;

	if (!t)
		return ;
	te_screen_destroy(t->screen);
	te_screen_destroy(t->back);
	ctmp = t->images;
	tmp = cm_chunk_it_next(ctmp);
	while (ctmp)
	{
		te_img_destroy((t_te_img *)tmp);
		tmp = cm_chunk_it_next(ctmp);
		if (!tmp)
			ctmp = cm_chunk_next(ctmp);
	}
	cm_chunk_clear(t->images, CM_CLEAR_FREE);
	te_set_mode(TE_MODE_BACKUP);
	te_ansi(TE_ANSI_CURSOR_ON);
	te_ansi(TE_ANSI_CLEAR TE_ANSI_RESET);
	free(t);
}

void	te_loop_end(t_terminal *t)
{
	t->active = 0;
}

void	te_handle_keys(t_terminal *t, char seq[4])
{
	const unsigned char	key = (unsigned char)seq[0];
	uint8_t				*states;
	t_hook_func			*hooks;
	void				**params;

	hooks = t->hook_table.hooks;
	params = t->hook_table.params;
	states = t->hook_table.states;
	if (key == TE_ESQ)
	{
		if (seq[1] == 91 && hooks[TE_ESCAPE | seq[2]])
			hooks[TE_ESCAPE | seq[2]](params[TE_ESCAPE | seq[2]]);
	}
	if (key > 0 && key < TE_ESCAPE)
	{
		if (states[key])
			states[key] = 0;
		if (hooks[TE_KEYDOWN | key])
			hooks[TE_KEYDOWN | key](params[TE_KEYDOWN | key]);
	}
}

void	te_loop(t_terminal *t)
{
	char		seq[4];

	while (t->active)
	{
		*(uint32_t *)seq = 0;
		if (read(STDIN_FILENO, &seq, 4) < 0)
			break ;
		if (seq[0] == TE_EOF)
			break ;
		te_handle_keys(t, seq);
		if (t->hook_table.hooks[TE_LOOP])
			t->hook_table.hooks[TE_LOOP](t->hook_table.params[TE_LOOP]);
		te_terminal_screen_shift(t);
		te_sleep(t->fps);
	}
}
