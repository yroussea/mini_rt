/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_miniRT.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 00:12:46 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/18 16:30:05 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FEATURES_MINIRT_H
# define FEATURES_MINIRT_H
# undef FEATURES_MINIRT_H
# ifndef __RT_FEATURES_H__
#  define __RT_FEATURES_H__

#  define RT_DEFAULT_NAME "miniRT"

// Allows rt to be used as a standalone application. This would open a
// main menu screen and allow the user to select a file to open.
#  define FEAT_APPLICATION 0

// Allows the user to pass flags to the CLI to change the behavior of the
// application.
#  define FEAT_CLI_FLAGS 0

// Allows .cub files to be parsed, because why not.
#  define FEAT_CUB_PARSER 0

// Allows the user to use '#' to comment lines in .rt files.
#  define FEAT_PARSER_COMMENTS 0

# endif // __RT_FEATURES_H__
#endif // FEATURES_MINIRT_H
