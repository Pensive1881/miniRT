#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include "mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define ESC_KEY 65307

typedef struct s_mlx
{
    void    *connection;
    void    *window;
    void    *image;
    char    *pixels;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}   t_mlx;

typedef struct s_vec3
{
    double  x;
    double  y;
    double  z;
}   t_vec3;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_ambient
{
    double  ratio;
    t_color color;
}   t_ambient;

typedef struct s_camera
{
    t_vec3   position;
    t_vec3  direction;
    t_vec3	right;
    t_vec3	up;
    int     fov;
}   t_camera;

typedef struct s_light
{
    t_vec3  position;
    double  ratio;
    t_color color;
}   t_light;

typedef struct s_sphere
{
    t_vec3  center;
    double  diameter;
    t_color color;
}   t_sphere;

typedef struct s_scene
{
    t_ambient   ambient;
    t_camera    camera;
    t_light     light;
    //t_sphere    sphere;
    t_object	*objects; //list of all shapes in the scene
    int         has_ambient;
    int         has_camera;
    int         has_light;
    int         has_sphere;
    int		width;
    int		height;
}   t_scene;

typedef	struct	s_ray
{
	t_vec3	origin;
	t_vec3	dir; //always normalised
}	t_ray;

typedef	struct	s_plane
{
	t_vec3	point; //any point that lies on the plane
	t_vec3	normal;
}	t_plane;
typedef	struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef	enum	e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef	struct s_object
{
	t_type	type;//sphere, plane, or cylinder
	union
    {
		t_sphere	sp;
		t_plane	pl;
		t_cylinder	cy;
	};
	t_color	color;
	struct	s_object	*next;
}	t_object;

typedef	struct	s_hit
{
	double	t;//distance along the ray to the hit
	t_vec3	point;//exact 3D coordinate of the hit
	t_vec3	normal;//surface direction at the hit point
	t_object	*object;//which object was hit(NULL = miss)
}	t_hit;
//parse_values.c
int     parse_double(const char *str, double *out);
int     parse_int(const char *str, int *out);
int     parse_vec3(const char *str, t_vec3 *out);
int     parse_color(const char *str, t_color *out);

//parse_elements.c
int     parse_ambient(char *line, t_scene *scene);
int     parse_camera(char *line, t_scene *scene);
int     parse_light(char *line, t_scene *scene);
int     parse_sphere(char *line, t_scene *scene);

// parse_scene.c
int     parse_scene(const char *filename, t_scene *scene);

//vec3 functions
t_vec3  vec3(double x, double y, double z);
t_vec3  vec3_add(t_vec3 a, t_vec3 b);
t_vec3  vec3_sub(t_vec3 a, t_vec3 b);
t_vec3  vec3_scale(t_vec3 v, double t);
double  vec3_dot(t_vec3 a, t_vec3 b);
t_vec3  vec3_cross(t_vec3 a, t_vec3 b);
double  vec3_len_sq(t_vec3 v);
double  vec3_len(t_vec3 v);
t_vec3  vec3_norm(t_vec3 v);
t_vec3  vec3_mul(t_vec3 a, t_vec3 b);

//sphere.c
double  intersect_sphere(t_ray ray, t_sphere *sp);
t_vec3  sphere_normal(t_sphere *sp, t_vec3 hit_point);

//ray.c
t_vec3  ray_at(t_ray r, double t);

//camera.c
void    camera_init(t_camera *cam);
t_ray   get_ray(t_camera *cam, int px, int py, int width, int height);

//render.c
void    render(t_scene *scene, t_mlx *mlx);

//mlx_app.c
int     mlx_app_init(t_mlx *mlx, int width, int height);
void    mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int     mlx_close(t_mlx *mlx);
int     handle_key(int keycode, t_mlx *mlx);

//lighting.c
t_vec3	shade(t_scene *scene, t_color obj_colour, t_vec3 hit_point, t_vec3 normal);
t_vec3	calc_ambient(t_scene *scene, t_color obj_colour);
t_vec3	calc_diffuse(t_scene *scene, t_color obj_colour, t_vec3 hit_point, t_vec3 normal);

//objects.c
t_object    *create_object(t_type type, t_color color);
void        add_object(t_scene *scene, t_object *obj);
void        free_objects(t_object *objects);
#endif
