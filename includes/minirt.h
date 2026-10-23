/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:46:55 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/23 17:36:35 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "float.h"
# include <limits.h>
# include "libft.h"
# include "mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define ESC_KEY 65307
# ifdef __APPLE__
#  define ESC_KEY 53
# else
#  define ESC_KEY 65307
# endif

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_object	t_object;
typedef struct s_object	t_obj;

struct s_object
{
	t_type				type;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
	t_color				color;
	t_object			*next;
};

typedef struct s_mlx
{
	void		*connection;
	void		*window;
	void		*image;
	char		*pixels;
	t_object	*objects;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}			t_mlx;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}		t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	right;
	t_vec3	up;
	int		fov;
}		t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	ratio;
	t_color	color;
}		t_light;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_object	*objects;
	int			has_ambient;
	int			has_camera;
	int			has_light;
	int			has_sphere;
	int			width;
	int			height;
}				t_scene;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}		t_ray;

typedef struct s_hit
{
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_object	*object;
}			t_hit;

typedef struct s_quadr
{
	double	a;
	double	b;
	double	c;
}		t_quadr;

typedef struct s_px
{
	int	x;
	int	y;
	int	width;
	int	height;
}		t_px;

typedef struct s_cy_args
{
	t_vec3	center;
	t_vec3	axis;
	t_color	color;
	double	diameter;
	double	height;
}		t_cy_args;

//parse_values.c
int		parse_double(const char *str, double *out);
int		parse_int(const char *str, int *out);
int		parse_vec3(const char *str, t_vec3 *out);
int		parse_color(const char *str, t_color *out);

//parse_elements.c
int		parse_ambient(char *line, t_scene *scene);
int		parse_camera(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		valid_orientation(t_vec3 vector);
char	*next_token(char **cursor);

// parse_scene.c
int		parse_scene(const char *filename, t_scene *scene);

//vec3 functions
t_vec3	vec3(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double t);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_len_sq(t_vec3 v);
double	vec3_len(t_vec3 v);
t_vec3	vec3_norm(t_vec3 v);
t_vec3	vec3_mul(t_vec3 a, t_vec3 b);

//sphere.c
double	intersect_sphere(t_ray ray, t_sphere *sp);
t_vec3	sphere_normal(t_sphere *sp, t_vec3 hit_point);

//ray.c
t_vec3	ray_at(t_ray r, double t);

//camera.c
void	camera_init(t_camera *cam);
t_ray	get_ray(t_camera *cam, t_px px);

//render.c
void	render(t_scene *scene, t_mlx *mlx);

//mlx_app.c
int		mlx_app_init(t_mlx *mlx, int width, int height);
void	mlx_put_pixel(t_mlx *mlx, int x, int y, int color);
int		mlx_close(t_mlx *mlx);
int		handle_key(int keycode, t_mlx *mlx);

//lighting.c
t_vec3	shade(t_scene *scene, t_color obj_colour, t_vec3 hit, t_vec3 normal);
t_vec3	calc_ambient(t_scene *scene, t_color obj_colour);
t_vec3	calc_diffuse(t_scene *scene, t_color obj_col, t_vec3 hit, t_vec3 norm);

//objects.c
t_obj	*create_object(t_type type, t_color color);
void	add_object(t_scene *scene, t_object *obj);
void	free_objects(t_object *objects);

//plane_stub.c
double	intersect_plane(t_ray ray, t_plane *pl);
t_vec3	plane_normal(t_plane *pl);

//cylinder.c
double	intersect_cylinder(t_ray ray, t_cylinder *cy);
t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 hit_point);
int		valid_side_t(t_ray ray, t_cylinder *cy, double t);

//cylinder_utils.c
int		solve_quadr(t_quadr q, double *t1, double *t2);
double	solve_side(t_ray ray, t_cylinder *cy);
t_quadr	get_cy_coeffs(t_ray ray, t_cylinder *cy);

//utils.c
void	print_scene(const t_scene *scene);
#endif
