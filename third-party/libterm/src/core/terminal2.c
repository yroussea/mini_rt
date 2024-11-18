/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 23:49:33 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 23:51:19 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <termengine.h>
#include <unistd.h>

uint32_t	te_set_mode(uint32_t mode)
{
	struct termios			attr;
	static struct termios	back;

	if (!isatty(STDIN_FILENO))
		return (1);
	tcgetattr(STDIN_FILENO, &back);
	if (mode == TE_MODE_RENDER)
	{
		attr = back;
		attr.c_lflag &= ~(ICANON | ECHO);
		attr.c_cc[VMIN] = 0;
		attr.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
	}
	else
		tcsetattr(STDIN_FILENO, TCSANOW, &back);
	return (0);
}

void	te_terminal_get_size(uint32_t *row, uint32_t *col)
{
	struct winsize	win;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &win);
	*row = win.ws_row;
	*col = win.ws_col;
}
