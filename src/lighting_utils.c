#include "minirt.h"

static t_vec3 colour_to_vec3(t_color c)
{
	return (vec3(c.r, c.g, c.b));
}

//ambient :: ratio x ambient_colour x obj_colour

t_vec3	calc_ambient(t_scene *scene, t_color obj_colour)
{
	t_vec3	ambient_col;
	t_vec3	obj;

	ambient_col = colour_to_vec3(scene->ambient.color);
	obj = colour_to_vec3(obj_colour);
	return (vec3_scale(vec3_mul(ambient_col, obj), scene->ambient.ratio / 255.0));
}

t_vec3	calc_diffuse(t_scene *scene, t_color obj_colour, t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	light_dir;
	double	intensity;
	t_vec3	obj;
	t_vec3	light_col;

	light_dir = vec3_norm(vec3_sub(scene->light.position, hit_point));
	intensity = vec3_dot(normal, light_dir);
	if (intensity < 0.0)
		intensity = 0.0;
	intensity = intensity * scene->light.ratio;
	obj = colour_to_vec3(obj_colour);
	light_col = colour_to_vec3(scene->light.color);
	return (vec3_scale(vec3_mul(obj, light_col), intensity / 255.0));
}
