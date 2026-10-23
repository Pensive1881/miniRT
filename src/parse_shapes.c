/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 16:58:11 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/23 18:35:59 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// parses the sphere values
int	parse_sphere(char *line, t_scene *scene)
{
	char		*cursor;
	char		*token;
	t_sphere	value;
	t_object	*object;

	cursor = line;
	token = next_token(&cursor);
	token = next_token(&cursor);
	if (!token || !parse_vec3(token, &value.center))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_double(token, &value.diameter))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_color(token, &value.color))
		return (0);
	if (next_token(&cursor) || value.diameter <= 0.0)
		return (0);
	object = create_object(SPHERE, value.color);
	if (!object)
		return (0);
	object->sp = value;
	add_object(scene, object);
	return (1);
}

static int	parse_plane_args(char *line, t_plane *value, t_color *color)
{
	char		*cursor;
	char		*token;

	cursor = line;
	token = next_token(&cursor);
	token = next_token(&cursor);
	if (!token || !parse_vec3(token, &value->point))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_vec3(token, &value->normal))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_color(token, color))
		return (0);
	if (next_token(&cursor) || !valid_orientation(value->normal))
		return (0);
	return (1);
}

int	parse_plane(char *line, t_scene *scene)
{
	t_plane		value;
	t_color		color;
	t_object	*object;

	if (!parse_plane_args(line, &value, &color))
		return (0);
	object = create_object(PLANE, color);
	if (!object)
		return (0);
	object->pl.point = value.point;
	object->pl.normal = vec3_norm(value.normal);
	add_object(scene, object);
	return (1);
}

static	int	parse_cy_args(char *line, t_cy_args *args)
{
	char	*cursor;
	char	*token;

	cursor = line;
	token = next_token(&cursor);
	token = next_token(&cursor);
	if (!token || !parse_vec3(token, &args->center))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_vec3(token, &args->axis))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_double(token, &args->diameter))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_double(token, &args->height))
		return (0);
	token = next_token(&cursor);
	if (!token || !parse_color(token, &args->color))
		return (0);
	return (!next_token(&cursor));
}

int	parse_cylinder(char *line, t_scene *scene)
{
	t_cy_args	args;
	t_object	*object;

	if (!parse_cy_args(line, &args))
		return (0);
	if (!valid_orientation(args.axis) 
		|| args.diameter <= 0.0 || args.height <= 0.0)
		return (0);
	object = create_object(CYLINDER, args.color);
	if (!object)
		return (0);
	object->cy.center = args.center;
	object->cy.axis = vec3_norm(args.axis);
	object->cy.radius = args.diameter / 2.0;
	object->cy.height = args.height;
	add_object(scene, object);
	return (1);
}
