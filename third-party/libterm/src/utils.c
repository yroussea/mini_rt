/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:05:50 by rgramati          #+#    #+#             */
/*   Updated: 2024/11/17 23:56:36 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <sys/time.h>
#include <termengine.h>
#include <unistd.h>

void	te_terminal_fps_max(t_terminal *term, uint32_t fps)
{
	if (fps == 0 || fps > 120)
		return ;
	term->fps = fps;
}

void	te_sleep(uint32_t fps)
{
	struct timeval	start;
	struct timeval	end;
	uint64_t		elapsed_time;
	uint64_t		sleep_time;

	sleep_time = 1000000 / fps;
	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&end, NULL);
		elapsed_time = (end.tv_sec - start.tv_sec) * 1000000
			+ (end.tv_usec - start.tv_usec);
		if (elapsed_time >= sleep_time)
			break ;
		usleep(30);
	}
}

#ifdef _STDIO_H

/**
* @brief	Writes ansi sequences using printf (only if stdio defined).
*
* @param	(const char *seq)		Ansi sequence.
*/
void	te_ansi(const char *seq)
{
	printf("%s", seq);
}

#else
# ifdef FT_PRINTF_H

/**
* @brief	Writes ansi sequences using ft_printf (only if included)
*
* @param	(const char *)		Ansi sequence.
*/
void	te_ansi(const char *seq)
{
	ft_printf("%s", seq);
}

# else

/**
* @brief	Writes ansi sequences using write (default if no printf included)
*
* @param	(const char *)		Ansi sequence.
*/
void	te_ansi(const char *seq)
{
	const char	*tmp;

	tmp = seq;
	while (*tmp)
		tmp++;
	write(STDIN_FILENO, seq, tmp - seq);
}

# endif	// FT_PRINTF_H
#endif	// _STDIO_H
