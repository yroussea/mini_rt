/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:49:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/10/13 15:28:39 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <mlx.h>

# define COLOR_RESET "\033[1;0m"
# define COLOR_BLACK	"\033[1;30m"
# define COLOR_RED		"\033[1;31m"
# define COLOR_GREEN	"\033[1;32m"
# define COLOR_YELLOW	"\033[1;33m"
# define COLOR_BLUE		"\033[1;34m"
# define COLOR_MAGENTA	"\033[1;35m"
# define COLOR_CYAN		"\033[1;36m"
# define COLOR_WHITE	"\033[1;37m"

# define VEC0 (t_vec3d){0,0,0}
# define RED (t_vec3d){1,0,0}
# define BLUE (t_vec3d){0,0,1}
# define GREEN (t_vec3d){0,1,0}
# define GREY (t_vec3d){0.2,0.2,0.2}
# define BLACK (t_vec3d){0,0,0}
# define WHITE (t_vec3d){1,1,1}

#endif
