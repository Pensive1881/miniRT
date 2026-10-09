#include "minirt.h"

static	double	hit_cap(t_ray ray, t_vec3 cap_center, t_vec3 cap_normal, double radiou)
{
	double	denom;
	double	t;
	t_vec3	hit;
	t_vec3	to_hit;

	denom = vec3_dot(ray.dir, cap_normal);
	//ray parallel to cap plane(is a miss)
	if (denom > -1e-8 && denom < 1e-8)
		return (-1);
	t = vec3_dot(vec3_sub(cap_center, ray.origin), cap_normal) / denom;
	//cap is behind the camera
	if (t < 1e-6)
		return (-1);
	hit = ray_at(ray, t);
	to_hit = vec3_sub(hit, cap_center);
	//hit outside the dark radius
	if (vec3_len(to_hit) > radius)
		return (-1);
	return (t);
}

/*checking t from the side quadratic: valid if t > 1e-6
 AND the hit is within[0, height] along the axis*/
static	double	check_side_t(t_ray ray, t_cylinder *cy, double t)
{
	t_ec3	hit;
	double	along;

	if (t < 1e-6)
		return (-1);
	hit = ray_at(ray, t);
	along = vec3_dot(vec3_sub(hit, cy->center), cy->axis);
	//outside the height range
	if (along < 0 || along > cy->height)
		return (-1);
	return (t);
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
