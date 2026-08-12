
#include "minirt.h"

//creating a 3d vector
t_vec3	vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

//adding two vectors together
//helpes finding the direction between two points. 
//if i am standing at point a and walk to point b, adding them together is the new loc
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

//subtraction
//example: if we have a light bulb at A and a wall at B, by sutracting 
//b from a we can get an arrow vector pointing from wall directly to light.

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

//Multiplies a vector by a no(a scale(t), which stretches or shrinks it.
//ex: walking down a light ray. a ray has a starting point and a direction
//by scaling the direction by time(t), we can calculate exactly where the ray
//is in 3D space at that exact moment.

vex3	vec3_scale(t_vec3 v, double t)
{
	return (vec3(v.x * t, v.y * t, v.z * t));
}

//dot production
//calculate shadows and lighting. it tell how directly a surface is facing a light source.
//a surface facing the light directly gets a dot produt(bright), while a tilted away 
//surface gets A low dot production(dark).

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x + a.y * b.y + a.z * b.z));
}

