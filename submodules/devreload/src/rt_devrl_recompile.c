/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_devrl_recompile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:36:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/16 07:06:37 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <rt/devreload.h>
#include <rt/log.h>
#include <limits.h>
#include <unistd.h>

#ifndef RT_DEVRELOAD_DAEMON_FILE
# error "RT_DEVRELOAD_DAEMON_FILE is not defined"
#endif
#ifndef RT_DEVRELOAD_DAEMON_PAYLOAD_FILE
# error "RT_DEVRELOAD_DAEMON_PAYLOAD_FILE is not defined"
#endif
#ifndef RT_DEVRELOAD_DAEMON_RETURN_FILE
# error "RT_DEVRELOAD_DAEMON_RETURN_FILE is not defined"
#endif
#ifndef RT_DEVRELOAD_DAEMON_ACK_FILE
# error "RT_DEVRELOAD_DAEMON_ACK_FILE is not defined"
#endif

static int	rt_devrl_check_daemon(t_rt *rt)
{
	const char	*target_file = RT_DEVRELOAD_DAEMON_FILE;
	const int	fd = open(target_file, O_RDONLY);

	rt_trace(rt, "devrl: checking for daemon\n");
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static void	rt_devrl_write_payload(t_rt *rt)
{
	const char	*target_file = RT_DEVRELOAD_DAEMON_PAYLOAD_FILE;
	const int	fd = open(target_file, O_RDWR | O_CREAT, 0644);
	int			ret;

	if (fd == -1)
	{
		rt_error(rt, "rt_devrl_write_payload: open(%s) failed: %m\n",
			target_file);
		return ;
	}
	ret = write(fd, "payload\n", 8);
	close(fd);
	if (ret != 8)
	{
		rt_error(rt, "rt_devrl_write_payload: write(%s) failed: %m\n",
			target_file);
	}
	else
		rt_trace(rt, "devrl: payload written\n");
}

static void	rl_devrl_wait(t_rt *rt)
{
	int		threshold;
	int		fd;

	rt_trace(rt, "devrl: waiting for daemon to recompile\n");
	threshold = 0;
	while (1)
	{
		fd = open(RT_DEVRELOAD_DAEMON_RETURN_FILE, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			break ;
		}
		while (threshold == 0)
		{
			if (threshold++ > INT_MAX - 10)
				threshold = 0;
		}
	}
	rt_trace(rt, "daemon recompiled\n");
}

static void	rt_devrl_ack(__attribute__((unused)) t_rt *rt)
{
	const char	*target_file = RT_DEVRELOAD_DAEMON_ACK_FILE;
	const int	fd = open(target_file, O_RDWR | O_CREAT, 0644);

	if (fd == -1)
		return ;
	(void) !write(fd, "ack\n", 4);
	close(fd);
}

void	rt_devrl_recompile(t_rt *rt)
{
	if (!rt_devrl_check_daemon(rt))
	{
		rt_error(rt, "cannot recompile: daemon not running\n");
		return ;
	}
	rt_trace(rt, "devrl: writing payload to '%s'\n",
		RT_DEVRELOAD_DAEMON_PAYLOAD_FILE);
	rt_devrl_write_payload(rt);
	rl_devrl_wait(rt);
	rt_trace(rt, "devrl: acking daemon\n");
	rt_devrl_ack(rt);
}
