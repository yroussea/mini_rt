#ifndef OBJECT_H
# define OBJECT_H

# include <ft/math/vector.h>
# include <sys/types.h>

typedef struct s_ray
{
	t_vec3d	point;
	t_vec3d	center;
	t_vec3d	direction;
	t_vec3d	hit_point;
	t_vec3d	color;
	float	sq_len;
}				t_ray;

typedef struct s_sphere
{
	t_vec3d		center;
	float		rayon; //att diamettre pas rayon
	float		dot_production_rayon;
}				t_sphere;

typedef struct s_cylinder
{
	t_vec3d		center;
	t_vec3d		axis;
	float		diameter;
	float		height;
	t_vec3d		top_center;
	float		sq_radius;
}				t_cylinder;

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

typedef struct s_camera
{
	t_vec3d	point;
	t_vec3d	view_vector;
	float	fov;
	u_char	pixelisation;
}				t_camera;

typedef enum s_objs_type
{
	LIGHT_MASK = 8,
	OBJS_MASK = 16,
	CAMERA = 1,
	AMBIANCE_LIGHT = 9,
	POINT_LIGHT = 10,
	SPHERE = 17,
	PLANE = 18,
	CYLINDER = 19,
}			t_objs_type;


typedef struct s_objs
{
	void			*obj;
	t_objs_type		type;
	t_vec3d			colors; //a diff
	int				id;
	float			(*intersection)(t_ray ray, void *obj);
	t_vec3d			(*get_normal)(t_ray ray, void *obj);
	struct s_objs	*next;
}				t_objs;

float	closer(float t1, float t2);
t_objs	*sphere(t_vec3d center, float rayon, t_vec3d colors);

t_objs	*plane(t_vec3d normal, t_vec3d point, t_vec3d colors);
float	plane_intersect(t_ray ray, t_vec3d normal, t_vec3d point);

t_objs	*cylinder(t_vec3d coo, t_vec3d vect, float h, float diam, t_vec3d color);

t_objs	*light(t_vec3d coo, float intensity, t_objs_type type, t_vec3d color);
t_objs	*camera(t_vec3d coo, t_vec3d view_vector, float fov);

t_objs	*add_objects(t_objs *obj);
void	get_objs(t_objs	**x);

#endif
