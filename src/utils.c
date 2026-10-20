#include "minirt.h"

static void	print_ambient(const t_scene *scene)
{
	if (!scene->has_ambient)
		return ;
	printf("Ambient: ratio=%.2f colour=(%d,%d,%d)\n",
		scene->ambient.ratio,
		scene->ambient.color.r,
		scene->ambient.color.g,
		scene->ambient.color.b);
}

static void	print_camera(const t_scene *scene)
{
	if (!scene->has_camera)
		return ;
	printf("Camera: pos=(%.2f,%.2f,%.2f) dir=(%.2f,%.2f,%.2f) fov=%d\n",
		scene->camera.position.x, scene->camera.position.y,
		scene->camera.position.z,
		scene->camera.direction.x, scene->camera.direction.y,
		scene->camera.direction.z,
		scene->camera.fov);
}

static void	print_light(const t_scene *scene)
{
	if (!scene->has_light)
		return ;
	printf("Light: pos=(%.2f,%.2f,%.2f) ratio=%.2f color=(%d,%d,%d)\n",
		scene->light.position.x, scene->light.position.y,
		scene->light.position.z,
		scene->light.ratio,
		scene->light.color.r,
		scene->light.color.g,
		scene->light.color.b);
}

void	print_scene(const t_scene *scene)
{
	t_object	*obj;
	int	count;

	printf("Parsed scene:\n");
	print_ambient(scene);
	print_camera(scene);
	print_light(scene);
	obj = scene->objects;
	count = 0;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	printf("Objects in scene: %d\n", count);
}
