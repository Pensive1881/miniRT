/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:37:36 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 15:06:12 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//to get to wanted destinetion, direction vector can be mutiplied by t
//add that ditance vector to the ray's starting point
//function returns the final 3d point in space

t_vec3	ray_at(t_ray r, double t)
{
	t_vec3	scale_dir;
	t_vec3	hit_point;

	scale_dir = vec3_scale(r.dir, t);
	hit_point = vec3_add(r.origin, scale_dir);
	return (hit_point);
}
