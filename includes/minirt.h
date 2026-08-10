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
}   t_scene;

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

#endif
