/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:37:28 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/21 14:37:30 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadr(double a, double b, double c, double *t1, double *t2)
{
	double	disc;
	double	sqrt_disc;

	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	*t1 = (-b - sqrt_disc) / (2.0 * a); //closer root
	*t2 = (-b + sqrt_disc) / (2.0 * a); //farther root
	return (1);
}

double	solve_side(t_ray ray, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;

	get_cy_coeffs(ray, cy, &a, &b, &c);
	if (a < 1e-10 && a > -1e-10)
		return (-1);
	if (!solve_quadr(a, b, c, &t1, &t2))
		return (-1);
	if (valid_side_t(ray, cy, t1))
		return (t1);
	if (valid_side_t(ray,cy, t2))
		return (t2);
	return (-1);
}

/*get_cy_ computes the a,b,c of the quadratic equation for the ray VS
 infinite cylinder sie intersection
 * the game here is to project everything on the plane perpendicular to the axis
 * in that 2D plane the cylndr become a circle, and the ray become a 2d ray
 * solution: same as a circle intersection*/
void	get_cy_coeffs(t_ray ray, t_cylinder *cy, double *a, double *b, double *c)
{
	t_vec3	oc;
	t_vec3	di_perpend;
	t_vec3	oc_perpend;
	double	d_along;
	double	oc_along;
	//oc = ray origin - cy center(shift to cy's local space)
	oc = vec3_sub(ray.origin, cy->center);
	//project ray direction on axis, minus that component to get perpendi part
	d_along	= vec3_dot(ray.dir, cy->axis);
	di_perpend = vec3_sub(ray.dir, vec3_scale(cy->axis, d_along));
	oc_along = vec3_dot(oc, cy->axis);
	oc_perpend = vec3_sub(oc, vec3_scale(cy->axis, oc_along));
	//now we got to 2D circle problem
	*a = vec3_dot(di_perpend, di_perpend);
	*b = 2.0 * vec3_dot(di_perpend, oc_perpend);
	*c = vec3_dot(oc_perpend, oc_perpend) - (cy->radius * cy->radius);
}
