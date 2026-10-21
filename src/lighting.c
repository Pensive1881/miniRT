/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:36:59 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/21 14:37:00 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	clamp_colour(t_vec3 c);
static int	blocks_light(t_scene *scene, t_ray shadow_ray, double light_dist);

static	int	in_shadow(t_scene *scene, t_vec3 hit_point, t_vec3 normal)
{
	t_ray	shadow_ray;
	t_vec3	to_light;

	to_light = vec3_sub(scene->light.position, hit_point);
	shadow_ray = make_shadow_ray(hit_point, normal, to_light);
	return (block_light(scene, shadow_ray, vec3_len(to_light)));
}

static	int	block_light(t_scene *scene, t_ray shadow_ray, double light_dist)
{
	t_object	*obj;
	double	t;

	obj = scene->objects;
	while (obj)
	{
		t = -1;
		if (obj->type == SPHERE)
			t = intersect_sphere(shadow_ray, &obj->sp);
		else if (obj->type == PLANE)
			t = intersect_plane(shadow_ray, &obj->pl);
		else if (obj->type == CYLINDER)
			t = intersect_cylinder(shadow_ray, &obj->cy);
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
//ambient is allway applied
	ambient = calc_ambient(scene, obj_colour);
	//diffuse: only if not in shadow
	if (!in_shadow(scene, hit_point, normal))
		diffuse = calc_diffuse(scene, obj_colour, hit_point, normal);
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
