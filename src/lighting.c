/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:36:59 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 16:58:03 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static		t_vec3	clamp_colour(t_vec3 c);
static		int	block_light(t_scene *scene, t_ray shad_ray, double light_dist);

static	t_ray	make_shadow_ray(t_vec3 hit_poi, t_vec3 normal, t_vec3 to_light)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec3_add(hit_poi, vec3_scale(normal, 1e-4));
	shadow_ray.dir = vec3_norm(to_light);
	return (shadow_ray);
}

static	int	in_shadow(t_scene *scene, t_vec3 hit_point, t_vec3 normal)
{
	t_ray	shadow_ray;
	t_vec3	to_light;

	to_light = vec3_sub(scene->light.position, hit_point);
	shadow_ray = make_shadow_ray(hit_point, normal, to_light);
	return (block_light(scene, shadow_ray, vec3_len(to_light)));
}

static	int	block_light(t_scene *scene, t_ray shad_ray, double light_dist)
{
	t_object	*obj;
	double		t;

	obj = scene->objects;
	while (obj)
	{
		t = -1;
		if (obj->type == SPHERE)
			t = intersect_sphere(shad_ray, &obj->sp);
		else if (obj->type == PLANE)
			t = intersect_plane(shad_ray, &obj->pl);
		else if (obj->type == CYLINDER)
			t = intersect_cylinder(shad_ray, &obj->cy);
		if (t > 1e-6 && t < light_dist)
			return (1);
		obj = obj->next;
	}
	return (0);
}

//ambient is allway applied
//diffuse: only if not in shadow
t_vec3	shade(t_scene *scene, t_color obj_colour, t_vec3 hit, t_vec3 normal)
{
	t_vec3	ambient;
	t_vec3	diffuse;

	ambient = calc_ambient(scene, obj_colour);
	if (!in_shadow(scene, hit, normal))
		diffuse = calc_diffuse(scene, obj_colour, hit, normal);
	else
		diffuse = vec3(0, 0, 0);
	return (clamp_colour(vec3_add(ambient, diffuse)));
}

static	t_vec3	clamp_colour(t_vec3 c)
{
	if (c.x > 255.0)
		c.x = 255.0;
	if (c.y > 255.0)
		c.y = 255.0;
	if (c.z > 255.0)
		c.z = 255.0;
	if (c.x < 0.0)
		c.x = 0.0;
	if (c.y < 0.0)
		c.y = 0.0;
	if (c.z < 0.0)
		c.z = 0.0;
	return (c);
}
