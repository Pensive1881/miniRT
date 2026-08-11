#include "minirt.h"

t_vec3	ray_at(t_ray r, double t)
{
	t_vec3	scale_dir;
	t_vec3	hit_point;

	//to get to wanted destinetion, direction vector can be mutiplied by t
	scale_dir = vec3_scale(r.dir, t);
	//add that ditance vector to the ray's starting point
	hit_point = vec3_add(r.origin, scale_dir);
	return (hit_point); //the final 3d point in space
}
