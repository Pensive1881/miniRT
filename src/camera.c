#include "minirt.h"

//we will call this to build right and up from direction, after parsing
void	camera_init(t_camera *cam)
{
	t_vec3	world_up;

	cam->direction = vec3_norm(cam->direction);
	world_up = vec3(0, 1, 0);
	//if camera points straight up we need diffrent world up
	if (fabs(vec3_dot(cam->direction, world_up)) > 0.999)
		world_up = vec3(0, 0, 1);
	cam->right = vec3_norm(vec3_cross(cam->direction, world_up));
	cam->up = vec3_norm(vec3_cross(cam->right, cam->direction));
}

//one ray per pixel, we will call it in render loop
t_ray	get_ray(t_camera *cam, int px, int py, int width, int height)
{
	t_ray	ray;
	//field of view and viewport scaling
	//we need angles in radians not degrees
	double fov_rad = cam->fov * M_PI / 180.0;
	double	half_w = tan(fov_rad / 2.0); //veiwport halfwidth
	double	aspect = (double)width / height;//otherwise the object will appear stretched horizontally
	//pixel to viewport coordinate mapping(u, v)
	double	u = half_w * (2.0 * (px + 0.5) / width - 1.0);
	double	v = half_w / aspect * (1.0 - 2.0 * (py + 0.5) / height);
	//combine camera basis vectors to get world space direction
	dir = vec3_add(cam->direction, vec3_add(vec3_scale(cam->right, u),
				vec3_scale(cam->up, v)));
	//ray assembly
	//all perspective rays start at the camera's loation in space
	ray.origin = cam->position;
	//normalising dir rescales the direction arrow to a standard length of 1.0
	//which is required for intersection math
	ray.dir = vec3_norm(dir);
	return (ray);

}
