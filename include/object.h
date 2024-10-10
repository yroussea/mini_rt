#ifndef OBJECT_H
# define OBJECT_H

# include <ft/math/vector.h>

typedef struct s_ray
{
	t_vec3d	point;
	t_vec3d	center;
	t_vec3d	direction;
	t_vec3d	hit_point;
	t_vec3d	color;
}				t_ray;

typedef struct s_sphere
{
	t_vec3d		center;
	float		rayon;
	float		dot_production_rayon;
}				t_sphere;

typedef struct s_light
{
	t_vec3d			point;
	float			intensity;
}				t_light;

typedef struct s_plane
{
	t_vec3d	obj;
	t_vec3d	point;
	t_vec3d	normal;
}				t_plane;

typedef enum s_objs_type
{
	SPHERE,
	PLANE,
	AMBIANCE_LIGHT,
	POINT_LIGHT,
}			t_objs_type;


typedef struct s_objs
{
	int				id;
	t_objs_type		type;
	t_vec3d			colors;
	void			*obj;
	float			(*fcnt)(t_ray ray, void *obj);
	struct s_objs	*next;

}				t_objs;

t_objs	*light(t_vec3d coo, float intensity, t_objs_type type, t_vec3d color);
t_objs	*cylinder(t_vec3d coo, t_vec3d vector, float height, t_vec3d colors);
t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors);
t_objs	*sphere(t_vec3d center, float rayon, t_vec3d colors);

t_objs	*add_objects(t_objs *obj);

#endif
