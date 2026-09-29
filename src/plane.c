/*
 a plane is infinite and defined by:
 * a point on the plane (pl->point)
 * a normal vector perpendicular to it (pl->normal)
  */

#include "minirt.h"

/*denominator = dot(ray.dir, pl->normal)
     if |denominator| < 1e-8: ray is parallel to plane → miss, return -1
     t = dot(pl->point - ray.origin, pl->normal) / denominator
     if t > 1e-6: return t
     else: return -1 (hit is behind camera)

   The stub returns -1 so everything compiles and the sphere still renders.*/

double	intersect_plane(t_ray ray, t_plane *pl)
{
	double	denom;//dot(ray.dir, normal)--how much ray aims at plane
	double	t; //the distance along the ray to the hit point
	t_vec3	to_plane; // vector from ray orogin to a point on the plane
	
	denom = vec3_dot(ray.dir, pl->normal);
	if (denom > -1e-8 && denom < 1e-8)
		return (-1); // its a miss, as ray is parallel
	to_plane = vec3_sub(pl->point, ray.origin);
	t = vec3_dot(to_plane, pl->normal) / denom;
	if (t < 1e-6)
		return (-1); //miss to cuz the hit is behind the camera

	return (t); // this is a valid hit-- distance along the ray
}

/*the normal of plane is constant everywhere, it never changes.
 need to just return the stored normal vector*/

t_vec3	plane_normal(t_plane *pl)
{
	return (pl->normal);
	//always the same for a flate plane
}
