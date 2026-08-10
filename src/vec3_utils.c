#include "minirt.h"

//cross product 
//setting up the camera. if we know which way the camera is looking(forward)
//and know which way the sky is(up), crossing those two vectors gives the exact
//right and left direction, allowing to draw a flat 2D screen in a 3d world

t_vec3_cross(t_vec3 a, t_vec3 b)
{
	double	x;
	double	y;
	double	z;

	x = a.y * b.z - a.z * b.y;
	y = a.z * b.x - a.x * b.z;
	z = a.x * b.y - a.y * b.x;
	return (vec3(x, y, z));
}

//calculating the actual length of the vector using pythagorean theorem.
//this is used to find the distance. this tells exactly how far the camera is
//from an object it just hit,
//or how far a shadow casting object is from the light source.

double	vec3_len_sq(t_vec3 v)// to speed up the renderer
{
	return (vec3_dot(v, v));
}
double	vec3_len(t_vec3 v)
{
	return (sqrt(vec3_len_sq(v)));
}

//normalization
//when we want to know which way a ray is pointing, we normalize it so the math remains
//consistent. the '1e-8' check prevent the program from crashing if it tries to 
//divide a vector with 0 len

t_vec3	vec3_norm(t_vec3 v)
{
	double	len;

	len = vec3_len(v);
	if (len < 1e-8)
	{
		return (vec3(0, 0, 0));
	}
	return (vec3_scale(v, 1.0 / len));
}

//multipling vectors component by component aka colour blanding

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x * b.x, a.y * b.y, a.z * b.z));
}
