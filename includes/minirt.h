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
    dboule  z;
}   t_vec3;

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_colour;

typedef struct s_ambient
{
    double  ratio;
    t_color color;
}   t_ambient;

typedef struct s_camera
{
    t_vec   position;
    t_vec3  direction;
    int     fov;
}   t_camera;

typedef struct s_light
{
    t_vec3  position;
    double  ratio;
    t_color color;
}   t_light;

typedef stfuct s_sphere
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
    int         had_camera;
    int         has_light;
    int         has_sphere;
}   t_scene;

#endif