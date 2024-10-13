/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 23:52:39 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/13 04:11:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLI_H
# define CLI_H
# undef CLI_H
# ifndef __RT_CLI_H__
#  define __RT_CLI_H__

#  include <rt/app.h>
#  include <rt/features.h>

#  if FEAT_CLI_FLAGS
#   define CLI_VALID_OPTS "hvVr:o:"
#  else
#   define CLI_VALID_OPTS "hvV"
#  endif

int		rt_cli_parse(t_rt *rt, int argc, char **argv);
void	rt_cli_opt_help(t_rt *rt);
void	rt_cli_opt_version(t_rt *rt);

# endif // __RT_CLI_H__
#endif // CLI_H
