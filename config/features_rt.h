/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_rt.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:12:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 03:02:39 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURES_RT_H
# define FEATURES_RT_H
# undef FEATURES_RT_H
# ifndef __RT_FEATURES_H__
#  define __RT_FEATURES_H__

#  define RT_DEFAULT_NAME "rt"

// Allows rt to be used as a standalone application. This would open a
// main menu screen and allow the user to select a file to open.
#  define FEAT_APPLICATION 0

// Allows the user to pass flags to the CLI to change the behavior of the
// program.
#  define FEAT_CLI_FLAGS 1

// Allows .cub files to be parsed, because why not.
#  define FEAT_CUB_PARSER 0

# endif // __RT_FEATURES_H__
#endif // FEATURES_RT_H
