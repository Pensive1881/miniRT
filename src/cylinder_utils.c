/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:37:28 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 16:54:48 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadr(t_quadr q, double *t1, double *t2)
{
	double	disc;
	double	sqrt_disc;

	disc = q.b * q.b - 4.0 * q.a * q.c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	*t1 = (-q.b - sqrt_disc) / (2.0 * q.a);
	*t2 = (-q.b + sqrt_disc) / (2.0 * q.a);
	return (1);
}

double	solve_side(t_ray ray, t_cylinder *cy)
{
	t_quadr	q;
	double	t1;
	double	t2;

	q = get_cy_coeffs(ray, cy);
	if (q.a < 1e-10 && q.a > -1e-10)
		return (-1);
	if (!solve_quadr(q, &t1, &t2))
		return (-1);
	if (valid_side_t(ray, cy, t1))
		return (t1);
	if (valid_side_t(ray, cy, t2))
		return (t2);
	return (-1);
}

static	void	cy_perp(t_ray r, t_cylinder *cy, t_vec3 *dp, t_vec3 *op)
{
	t_vec3	oc;

	oc = vec3_sub(r.origin, cy->center);
	*dp = vec3_sub(r.dir, vec3_scale(cy->axis,
				vec3_dot(r.dir, cy->axis)));
	*op = vec3_sub(oc, vec3_scale(cy->axis,
				vec3_dot(oc, cy->axis)));
}

/*get_cy_ computes the a,b,c of the quadratic equation for the ray VS
 infinite cylinder sie intersection
 * the game here is to project everything on the plane perpendicular to the axis
 * in that 2D plane the cylndr become a circle, and the ray become a 2d ray
 * solution: same as a circle intersection*/
t_quadr	get_cy_coeffs(t_ray ray, t_cylinder *cy)
{
	t_quadr	q;
	t_vec3	di_perpend;
	t_vec3	oc_perpend;

	cy_perp(ray, cy, &di_perpend, &oc_perpend);
	q.a = vec3_dot(di_perpend, di_perpend);
	q.b = 2.0 * vec3_dot(di_perpend, oc_perpend);
	q.c = vec3_dot(oc_perpend, oc_perpend) - (cy->radius * cy->radius);
	return (q);
}
