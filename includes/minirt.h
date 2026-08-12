#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "mlx.h"

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
    t_sphere    sphere;
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
void    render(t_scene *scene);

#endif
