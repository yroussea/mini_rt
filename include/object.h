#ifndef OBJECT_H
# define OBJECT_H

typedef float	__attribute__((aligned(16),	vector_size(16)))	t_v4f;

typedef struct s_ray
{
	t_v4f	point;
	t_v4f	center;
	t_v4f	direction;
	t_v4f	hit_point;
	t_v4f	color;
}				t_ray;

typedef struct s_sphere
{
	t_v4f	center;
	t_v4f	rayon;
	float		dot_production_rayon;
}				t_sphere;

typedef struct s_tri
{
	t_v4f	normal;
	t_v4f	v1;
	t_v4f	v2;
	t_v4f	v3;
}				t_tri;

typedef struct s_plane
{
	t_v4f	obj;
	t_v4f	point;
	t_v4f	normal;
}				t_plane;

typedef enum s_objs_type
{
	SPHERE = 1u,
	PLANE = 1u << 1,
	TRIANGLE = 1u << 2,
}			t_objs_type;

typedef struct s_objs
{
	int				id;
	t_objs_type		type;
	t_v4f			colors;
	t_v4f			normal;
	void			*obj;
	struct s_objs	*next;
	float			(*fcnt)(t_ray ray, void *obj);

}				t_objs;

typedef enum s_light_type
{
	AMBIANCE,
	NORMAL,
}			t_light_type;

typedef struct s_light
{
	struct s_light	*next;
	t_light_type	type;
	t_v4f			point;
	float			intensity;
	t_v4f			color;
}				t_light;

void	add_objects_lights(t_objs **objs, t_light **lights);

#endif
