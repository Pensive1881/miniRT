#include "minirt.h"

//calculating whether a ray hits a sphere and returns
//the distance 't' to the closest hit

double	intersect_sphere(t_ray ray, t_sphere *sp)
{
	t_vec3	oc; //vector pointin fro sphere's center to ray's origin
	double	radius; //sphere radius
	double	a; // ray direction squared
	double	b; // projection of ray direction onto oc
	double	c; // distance from sphere surface to origin
	double	disc; // discrininant(b^2 - 4ac): determines number of hits
	double	t; // distance along the ray to the hit point

	//setting up sphere dimensions and center offset
	radius = sp->diameter / 2.0;
	oc = vec3_sub(ray.origin, sp->center);
	//calculating quadratic equation terms
	a = vec3_dot(ray.dir, ray.dir);
	b = 2.0 * vec3_dot(oc, ray.dir);
	c = vec3_dot(oc, oc) - radius * radius;
	//discriminant detrmines if ray intersect the sphere
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (-1);
	//finding the closest intersection point
	//1. closest to camera
	t = (-b - sqrt(disc)) / (2.0 * a);
	if (t > 1e-6)
		return (t);
	//2. hits the back surface of the sphere(used if camera is inside the sper)
	t = (-b + sqrt(disc)) / (2.0 * a);
	if (t > 1e-6)
		return (t);
	//and if both hit points are behind the camera (t <= 0)
	return (-1);
}

//calculating the surface normal at the exact point where ray struck the sphere
t_vec3	sphere_normal(t_sphere *sp, t_vec3 hit_point)
{
	t_vec3	outward_dir;
	t_vec3	normal;

	outward_dir = vec3_sub(hit_point, sp->center);//arrow pointing from center of sphere to the hit oint
	normal = vec3_norm(outward_dir);//normalising
	return (normal);
}

