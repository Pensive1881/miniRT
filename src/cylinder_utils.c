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

double	solve_side(t)
