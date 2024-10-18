/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:52:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:55:18 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H
# undef CLI_H
# ifndef __RT_CLI_H__
#  define __RT_CLI_H__

#  include <rt/app.h>
#  include <rt/features.h>
#  include <stdbool.h>

#  if FEAT_CLI_FLAGS
#   define CLI_VALID_OPTS "hvVb:f:o:"
#   define CLI_ARG_OPTS "bfo"
#  else
#   define CLI_VALID_OPTS "hvV"
#   define CLI_ARG_OPTS ""
#  endif

#  define CLI_PASS			0
#  define CLI_EXIT_SUCCESS	1
#  define CLI_EXIT_FAILURE	2

int		rt_cli_parse(t_rt *rt, int argc, const char **argv);
void	rt_cli_opt_help(t_rt *rt);
void	rt_cli_opt_version(t_rt *rt);

# endif // __RT_CLI_H__
#endif // CLI_H
