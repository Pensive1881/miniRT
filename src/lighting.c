#include "minirt.h"
//converts 
static t_vec3 colour_to_vec3(t_color c)
{
	return (vec3(c.r, c.g, c.b));
}

//ambient :: ratio x ambient_colour x obj_colour

t_vec3	calc_ambient(t_scene *scene, t_color obj_colour)
{
	t_vec3	amb;
	t_vec3	obj;

	amb = vec3_scale(colour_to_vec3(scene->ambient.color), scene->ambient.ratio);
	obj = colour_to_vec3(obj_colour);
	//changed the return to see the shades
	return (vec3_scale(vec3_mul(amb, vec3_scale(obj, 1.0 / 255.0)), 1.0 / 255.0));
	//scale obj to 0-1 so mul doesnt overflow
}

t_vec3	calc_diffuse(t_scene *scene, t_color obj_colour, t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	light_dir;
	double	intensity;
	t_vec3	obj;
	t_vec3	light_col;

	light_dir = vec3_norm(vec3_sub(scene->light.position, hit_point));
	intensity = vec3_dot(normal, light_dir);
	if (intensity < 0)
		intensity = 0;
	intensity = intensity * scene->light.ratio;
	obj = colour_to_vec3(obj_colour);
	light_col = colour_to_vec3(scene->light.color);
	return (vec3_scale(vec3_mul(obj, vec3_scale(light_col, 1.0/255.0)), intensity / 255.0));
}

static	int	in_shadow(t_scene *scene, t_vec3 hit_point, t_vec3 normal)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	double	light_distance;
	t_object	*obj;
	double	t;

	to_light = vec3_sub(scene->light.position, hit_point);
	light_distance = vec3_len(to_light);
	//to avoid self-hit
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(normal, 1e-6));
	shadow_ray.dir = vec3_norm(to_light);
	//new loop
	obj = scene->objects;
	while (obj)
	{
		t = -1;
		if (obj->type == SPHERE)
			t = intersect_sphere(shadow_ray, &obj->sp);
		else if (obj->type == PLANE)
			t = intersect_plane(shadow_ray, &obj->pl);
		//else if (obj->type == CYLINDER)
		//	t = intersect_cylinder(shadow_ray, &obj->cy);
		if (t > 1e-6 && t < light_distance)
			return (1);//something blocks the light = in shadow
		obj = obj->next;
	}
	return (0);
}

t_vec3	shade(t_scene *scene, t_color obj_colour, t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	ambient;
	t_vec3	diffuse;
	t_vec3	final;
//ambient is allway applied
	ambient = calc_ambient(scene, obj_colour);
	//diffuse: only if not in shadow
	if (!in_shadow(scene, hit_point, normal))
		diffuse = calc_diffuse(scene, obj_colour, hit_point, normal);
	else
		diffuse = vec3(0, 0, 0);
	//combining and scaling back to 0 - 255
	final = vec3_add(ambient, diffuse);
	final = vec3_scale(final, 255.0);
	//clamp: lighting math can push over 255
	if (final.x > 255)
		final.x = 255;
	if (final.y > 255)
		final.y = 255;
	if (final.z > 255)
		final.z = 255;
	return (final);
}
