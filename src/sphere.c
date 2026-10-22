/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:37:06 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 15:33:34 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*calculating whether a ray hits a sphere and returns
the distance 't' to the closest hit*/
//calculating quadratic equation terms

static	t_quadr	sphere_coeffs(t_ray ray, t_sphere *sp)
{
	t_vec3	oc;
	t_quadr	q;
	double	radius;

	radius = sp->diameter / 2.0;
	oc = vec3_sub(ray.origin, sp->center);
	q.a = vec3_dot(ray.dir, ray.dir);
	q.b = 2.0 * vec3_dot(oc, ray.dir);
	q.c = vec3_dot(oc, oc) - radius * radius;
	return (q);
}

double	intersect_sphere(t_ray ray, t_sphere *sp)
{
	t_quadr	q;
	double	t1;
	double	t2;

	q = sphere_coeffs(ray, sp);
	if (!solve_quadr(q, &t1, &t2))
		return (-1);
	if (t1 > 1e-6)
		return (t1);
	if (t2 > 1e-6)
		return (t2);
	return (-1);
}

//calculating the surface normal at the 
//exact point where ray struck the sphere
//outward_dir = vec3_sub(hit_point, sp->center);
//->>arrow pointing from center of sphere to the hit oint

t_vec3	sphere_normal(t_sphere *sp, t_vec3 hit_point)
{
	t_vec3	outward_dir;
	t_vec3	normal;

	outward_dir = vec3_sub(hit_point, sp->center);
	normal = vec3_norm(outward_dir);
	return (normal);
}
