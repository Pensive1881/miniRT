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
	(void)ray;
	(void)pl;
	return (-1);
}

/*the normal of plane is constant everywhere, it never changes.
 need to just return the stored normal vector*/

t_vec3	plane_normal(t_plane *pl)
{
	return (pl->normal);
	//always the same for a flate plane
}
