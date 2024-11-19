/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:59:40 by yroussea          #+#    #+#             */
/*   Updated: 2024/11/19 16:41:46 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H
# undef OPTION_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_OPTION_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_OPTION_H__

#  ifndef RT_COEF_DIFFUSE
#   define RT_COEF_DIFFUSE 0.5
#  endif
#  ifndef RT_COEF_SPECULAR
#   define RT_COEF_SPECULAR 0.7
#  endif
#  ifndef RT_COEF_EXPOS_SPECULAR
#   define RT_COEF_EXPOS_SPECULAR 32
#  endif

#  ifndef RT_NO_FISH_EYE
#   define RT_NO_FISH_EYE 1
#  endif

#  ifndef RT_RONDED_CYLINDER_LINK_CHECKERBOARD
#   define RT_RONDED_CYLINDER_LINK_CHECKERBOARD 1
#  endif
#  ifndef RT_RONDED_CONE_LINKED_SURFACE
#   define RT_RONDED_CONE_LINKED_SURFACE 1 
#  endif
#  define RT_BOUNDING_BOX 0

#  ifndef RT_CHECKER_SIZE
#   define RT_CHECKER_SIZE 10
#  endif
#  ifndef RT_SCALE_BUMPMAP
#   define RT_SCALE_BUMPMAP 10
#  endif

# endif // __RT_RENDER_BACKEND_RAYTRACER_OPTION_H__
#endif // OPTION_H
