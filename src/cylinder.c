#include "minirt.h"

t_vec3	cylinder_normal(t_cylinder *cy, t_vec3 hit_point)
{
	(void)cy;
	(void)hit_point;
	return (vec3(0, 1, 0));
}
