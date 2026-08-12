#include "minirt.h"

static	int vec3_to_colour(t_vec3 c)//will use it one our mlx funtions are ready
				    //to be passed thr
{
	int	r = (int)(c.x);
	int	g = (int)(c.y);
	int	b = (int)(c.z);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);

}
void	render(t_scene *scene)
{
	int	x; //left to right (0 to width -1)
	int	y; //top to bottom (0 to heigth -1)
	t_ray	ray;
	double	t; // if positive, ray hit something; negetive, ray mised everything!
	t_vec3	colour;
	t_vec3	hit_point;//the exact 3d cord where ray touched the sphre surface
	t_vec3	normal;//the surface direction at the hit point
	
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = get_ray(&scene->camera, x, y, scene->width, scene->height);
			t = intersect_sphere(ray, &scene->sphere);
			if (t > 1e-6)
			{
				hit_point = ray_at(ray, t);
				normal = sphere_normal(&scene->sphere, hit_point);
				colour = vec3((normal.x + 1) * 127.5,
						(normal.y + 1) * 127.5,
						(normal.z + 1) * 127.5);
			}
			else
				colour = vec3(0, 0, 0);
			out_image_put_pixel();
			x++;
		}
		y++;
	}
	the mlx put image to window function()

}
