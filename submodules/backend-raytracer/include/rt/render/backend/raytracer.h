/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:43:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/06 20:40:02 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H
# undef RAYTRACER_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_H__

#  include <rt/render/backend.h>
#  include <rt/render/backend/raytracer/ray.h>
#  include <rt/render/backend/raytracer/objs.h>

#  define EPSILON 1e-2

typedef struct s_rt_backend_raytracer
{
	t_color		*buffer;
	uint64_t	ticker;
}	t_rt_backend_raytracer;

int				rt_backend_raytracer_init(t_rt_backend *self);
void			rt_backend_raytracer_destroy(t_rt_backend *self);
t_color			*rt_backend_raytracer_render(t_rt_backend *self);

t_rt_backend	*rt_backend_raytracer_provider(t_rt *rt, const char *name,
					size_t width, size_t height);

void			rt_backend_raytracer_get_shading(t_objs *objs,
					t_objs *obj_hit, t_ray *ray);
double			rt_backend_raytracer_find_obj_hit(t_ray *ray,
					t_objs *objs, t_objs **hit);
//utils
#  include <ft/math/matrix.h>
double			ft_fmod(double x, double y);
t_mat3d			m3d(t_vec3d col1, t_vec3d col2, t_vec3d col3);
t_vec3d			m3d_solv(t_mat3d a, t_vec3d b);

# endif // __RT_RENDER_BACKEND_RAYTRACER_H__
#endif // RAYTRACER_H
