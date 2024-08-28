/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:49:02 by yroussea          #+#    #+#             */
/*   Updated: 2024/08/28 07:05:52 by yroussea         ###   ########.fr       */
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

# define SIZE 1.5
# define WIDTH (960*SIZE)
# define HEIGHT (540*SIZE)
# define PIXEL (1)

# define VEC0 (t_v4f){0,0,0,0}
# define RED (t_v4f){1,0,0,0}
# define BLUE (t_v4f){0,0,1,0}
# define GREEN (t_v4f){0,1,0,0}
# define GREY (t_v4f){0.2,0.2,0.2,0}
# define BLACK (t_v4f){0,0,0,0}
# define WHITE (t_v4f){1,1,1,0}

#endif
