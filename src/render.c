#include "minirt.h"

/*walk the entire object list and finds what the ray hits first. 
 * fills in the hit struct with distance, point, normal, and which object.
 * return 1 if something was hit, 0 if the ray hit nothing (background)*/

static	int find_closest_hit(t_scene *scene, t_ray ray, t_hit *hit)
{
	t_object	*obj;
	double	t;
	double	closest;

	closest = 1e9;//start with infinity far away
	hit->object = NULL;
	obj = scene->objects;//start at the first object in the list
	while (obj)
	{
		t = -1; //default : this object does not get hit
		if (obj->type == SPHERE)
			t = intersect_sphere(ray, &obj->sp);
		else if (obj->type == PLANE)
			t = intersect_plane(ray, &obj->pl);
		//else if (obj->type == CYLINDER)
			//t = intersect_sylinder(ray, &obj->);
		/*is this hit valid and closer than what we already
		 found? if yes, it becomes the new closest hit*/
		if (t > 1e-6 && t < closest)
		{
			closest = t;
			hit->object = obj;
			hit->t = t;
		}
		obj = obj->next;
	}
	if (!hit->object)
		return (0);
	hit->point = ray_at(ray, hit->t);
	if (hit->object->type == SPHERE)
		hit->normal = sphere_normal(&hit->object->sp, hit->point);
	else if (hit->object->type == PLANE)
		hit->normal = plane_normal(&hit->object->pl);
	//else if (hit->object->type == CYLINDER)
	//	hit->normal = cylinder_normal(&hit->object->, hit->point);
	return (1);
}

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
void	render(t_scene *scene, t_mlx *mlx)
{
	int	x; //left to right (0 to width -1)
	int	y; //top to bottom (0 to heigth -1)
	t_ray	ray;
	t_vec3	colour;
	t_hit	hit_point;//the exact 3d cord where ray touched the sphre surface
	
	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			ray = get_ray(&scene->camera, x, y, scene->width, scene->height);
			if (find_closest_hit(scene, ray, &hit_point))
			{
				colour = shade(scene, hit_point.object->color, hit_point.point, hit_point.normal);
			}
			else
			{
				colour = vec3(0, 0, 0);
			}
			mlx_put_pixel(mlx, x, y, vec3_to_colour(colour));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->connection, mlx->window, mlx->image, 0, 0);
}
