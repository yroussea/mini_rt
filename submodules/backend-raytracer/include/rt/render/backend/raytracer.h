/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 08:43:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/11/17 18:04:39 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H
# undef RAYTRACER_H
# ifndef __RT_RENDER_BACKEND_RAYTRACER_H__
#  define __RT_RENDER_BACKEND_RAYTRACER_H__

#  include <ft/math/vector.h>
#  include <ft/math/matrix.h>
#  include <rt/render/backend.h>
#  include <rt/render/backend/raytracer/aabb.h>
#  include <rt/render/backend/raytracer/objects.h>
#  include <rt/render/backend/raytracer/ray.h>
#  include <rt/render/backend/raytracer/utils.h>
#  include <rt/objects.h>
#  include <math.h>
#  include <stddef.h>

// Youenn moment.
#  define EPSILON 1e-2

typedef struct s_rt_backend_raytracer
{
	t_color		*buffer;

	t_camera	*camera;
	t_ray		*rays;
	size_t		rays_alignment_offset;

	uint64_t	ticker;
}	t_rt_backend_raytracer;

int				rt_backend_raytracer_init(t_rt_backend *self);
void			rt_backend_raytracer_destroy(t_rt_backend *self);
t_color			*rt_backend_raytracer_render(t_rt_backend *self);

t_rt_backend	*rt_backend_raytracer_provider(t_rt *rt, const char *name,
					size_t width, size_t height);

void			rt_backend_raytracer_get_shading(t_obj *objs,
					t_obj *obj_hit, t_ray *ray);
double			rt_backend_raytracer_find_obj_hit(t_ray *ray,
					t_obj *objs, t_obj **hit);

# endif // __RT_RENDER_BACKEND_RAYTRACER_H__
#endif // RAYTRACER_H
