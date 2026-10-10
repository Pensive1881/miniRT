#include "minirt.h"

static	double	hit_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_normal, double radiou)
{
	double	denom;
	double	t;
	t_vec3	to_cap;
	t_vec3	hit;
	t_vec3	diff;

	denom = vec3_dot(ray.dir, cap_normal);
	//ray parallel to cap plane(is a miss)
	if (denom > -1e-8 && denom < 1e-8)
		return (-1);
	//to_cap points from camera to the center of the cap
	to_cap = vec3_sub(cap_centter, ray.origin);
	//plane intersection: t = dot(to_cap, normal)/denom 
	t = vec3_dot(to_cap, cap_normal) / denom;
	//cap is behind the camera
	if (t < 1e-6)
		return (-1);
	hit = ray_at(ray, t);
	diff = vec3_sub(hit, cap_center);
	//hit outside the dark radius
	if (vec3_dot(diff, diff) > radius * radius)
		return (-1);
	return (t);
}

void	get_cy_coeffs(t_ray ray, t_cylinder *cy, double *a, double *b, double *c)
{}

/*checks if a quadratic solution t is a real side_hit
 * hit must be in front not behind the camera
 * hit point is between  the two caps 0 < along_axis < height*/
static	int	valid_side_t(t_ray ray, t_cylinder *cy, double t)
{
	t_vec3	hit;
	t_vec3	oc;
	double	along_axis;

	if (t < 1e-6)
		return (0);
	//find the 3d hit point, then show it on axis
	hit = ray_at(ray, t);
	oc = vec3_sub(hit, cy->center);
	along_axis = vec3_dot(oc, cy->axis);
	//hit must be between bottom(0) && top of the cylinder
	if (along_axis < 0.0 || along_axis > cy->height)
		return (0);
	return (1);
}

//helper returns smallest positive value from up to 3 candidates
static	double	smallest_positive(double a, double b, double c)
{
	double	best;

	best = -1;
	if (a > 1e-6 && (best < 0 || a < best))
		best = a;
	if (b > 1e-6 && (best < 0 || b < best))
		best = b;
	if (c > 1e-6 && (best < 0 || c < best))
		best = c;
	return (best);
}


//top cap, bottom cap, curved side. 
//we figureout which surface was hit by checking along_axis
t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 hit_point)
{
	double	along;
	t_vec3	axis_point;

	along = vec3_dot(vec3_sub(hit_point, cy->center), cy->axis);
	//top cap; hit at the very top
	if (along >= cy->height - 1e-6)
		return (cy->axis);
	//bottom cap; hit at the very bottom
	if (along <= 1e-6)
		return (vec3_scale(cy->axis, -1.0));
	//curved side; normal points from axis to hit point
	axis_point = vec3_add(cy->center, vec3_scale(cy->axis, along));
	return (vec3_norm(vec3_sub(hit_point, axis_point)));
}
