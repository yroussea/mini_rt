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
	t_v4f		center;
	float		rayon;
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
	SPHERE = 1,
	PLANE = 2,
	TRIANGLE = 4,
}			t_objs_type;

typedef enum s_reflexion
{
	FLAT = 1,
	MIROIR = 5,
}			t_reflexion;

typedef struct s_objs
{
	int				id;
	t_objs_type		type;
	t_reflexion		reflexion;
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

t_light	*light(t_v4f coo, float intensity, t_light_type type, t_v4f color);
t_objs	*cylinder(t_v4f coo, t_v4f vector, float height, t_v4f colors);

t_objs	*plane(t_v4f normal, t_v4f point, t_v4f colors);

t_objs	*triangle(t_v4f colors, t_v4f vertex1, t_v4f vertex2, t_v4f vertex3);

t_objs	*sphere(t_v4f center, t_v4f colors);

void	add_objects_id(t_objs *objs);
t_objs	*add_objects(t_objs *obj);
t_light	*add_lights(t_light *light);

#endif
