/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:36:55 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 17:01:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APP_H
# define APP_H
# undef APP_H
# ifndef __RT_APP_H__
#  define __RT_APP_H__

#  include <rt/flags.h>
#  include <rt/objects.h>

// Shadow declaration, see <rt/render/backend.h>
typedef struct s_rt_backend		t_rt_backend;
// Shadow declaration, see <rt/render/frontend.h>
typedef struct s_rt_frontend	t_rt_frontend;

typedef struct s_rt_app
{
	const char		*executable;
	const char		*name;
	t_rt_flags		flags;

	size_t			width;
	size_t			height;

	t_rt_frontend	*frontend;
	const char		*queued_frontend;

	t_rt_backend	*backend;
}	t_rt;

int		rt_init(t_rt *rt, int argc, const char **argv, const char **envp);
void	rt_destroy(t_rt *rt);
void	rt_exit(t_rt *rt, int exit_code);

void	rt_resize(t_rt *rt, size_t width, size_t height);

void	rt_noop(void);

# endif // __RT_APP_H__
#endif // APP_H
