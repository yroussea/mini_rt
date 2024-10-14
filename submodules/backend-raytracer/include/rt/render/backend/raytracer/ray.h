/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:51:32 by kiroussa          #+#    #+#             */
/*   Updated: 2024/10/14 08:52:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# undef RAY_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_RAY_H__

#  include <ft/math/vector.h>
#  include <rt/color.h>

typedef struct s_ray
{
	t_vec3d	point;
	t_vec3d	center;
	t_vec3d	direction;
	t_vec3d	hit_point;
	t_color	color;
}	t_ray;

# endif // __RT_RENDER_BACKEND_RAYTRACER_RAY_H__
#endif // RAY_H
