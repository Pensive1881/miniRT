#include "minirt.h"

t_object	*create_object(t_type type, t_color color)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		return (NULL);
	ft_bzero(obj, sizeof(t_object));//zero all fields (shape data = 0)
	obj->type = type;//sphere, plane, or cylinder
	obj->color = color;
	obj->next = NULL;
	return (obj);
}

/*Appends an object to the END of the scene's object list.
   If the list is empty, obj becomes the first element.
   This preserves the order objects appear in the .rt file.*/
void	add_object(t_scene *scene, t_object *obj)
{
	t_object	*current;
	if (!scene->objects)
	{
		scene->objects = obj;
		return ;
	}
	current = scene->objects;
	while (current->next)
		current = current->next;
	current->next = obj;
}

void	free_objects(t_object *objects)
{
	t_object	*next;

	while (objects->next)
	{
		next = objects->next;
		free(objects);
		objects = next;
	}
}
