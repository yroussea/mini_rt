/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_check_reload.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:19:58 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/27 00:47:52 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft/mem.h>
#include <rt/devreload.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef RT_DEVRELOAD_DAEMON_WATCH_FILE
# error "RT_DEVRELOAD_DAEMON_WATCH_FILE not defined"
#endif

// stat syscall
#define SYS_STAT 0x4

long	ft_syscall(long number, ...);

static int	rt_stat(const char *path, struct stat *st)
{
	return (ft_syscall(SYS_STAT, path, st));
}

static bool	rt_devrl_check_file(const char *path)
{
	struct stat	st;

	ft_memset(&st, 0, sizeof(struct stat));
	if (rt_stat(path, &st) == -1)
		return (false);
	return (S_ISREG(st.st_mode));
}

static void	rt_devrl_update_watch_file(const char *path)
{
	const int	fd = open(path, O_RDONLY);

	if (fd == -1)
		return ;
	close(fd);
}

//TODO: reload frontend
void	rt_devrl_check_reload(t_rt *rt)
{
	if (rt_devrl_check_file(RT_DEVRELOAD_DAEMON_WATCH_FILE))
	{
		rt_devrl_update_watch_file(RT_DEVRELOAD_DAEMON_WATCH_FILE);
		rt_trace(rt, "daemon file changed, reloading...\n");
		rt_backend_reload(rt);
	}
}
