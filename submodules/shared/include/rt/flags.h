/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:40:17 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/18 18:50:24 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H
# undef FLAGS_H
# ifndef __RT_FLAGS_H__
#  define __RT_FLAGS_H__

#  include <stddef.h>
#  include <stdbool.h>

enum e_rt_mode
{
	RT_MODE_APP = 0,
	RT_MODE_RENDER_ONCE,
	RT_MODE_RENDER_LOOP,
	RT_MODE_PARSER_TEST,
};

typedef struct s_rt_flags
{
	enum e_rt_mode	mode;
	size_t			verbosity;

	const char		*filepath;

	const char		*output;

	const char		*frontend;
	const char		*backend;

	bool			no_unique;
}	t_rt_flags;

# endif // __RT_FLAGS_H__
#endif // FLAGS_H
