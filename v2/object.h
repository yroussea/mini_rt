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

typedef struct s_light
{
	t_v4f			point;
	float			intensity;
}				t_light;

typedef enum s_objs_type
{
	O_SPHERE,
	O_PLANE,
	O_TRIANGLE,
	L_AMBIANCE,
	L_NORMAL,
}			t_objs_type;

typedef struct s_objs
{
	int				id;
	t_objs_type		type;
	void			*obj;
	t_v4f			color;
	float			(*fcnt)(t_ray ray, void *obj);

}				t_objs;


t_objs	*light(t_v4f coo, float intensity, t_objs_type type, t_v4f color);
t_objs	*cylinder(t_v4f coo, t_v4f vector, float height, t_v4f colors);
t_objs	*plane(t_v4f normal, t_v4f point, t_v4f colors);
t_objs	*camera(t_vec3d coo, t_vec3d view_vector, float fov);
t_objs	*sphere(t_v4f center, t_v4f colors);

t_objs	*add_objects(t_objs *obj);

#endif
