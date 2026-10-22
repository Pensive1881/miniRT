/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:39:19 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 16:59:06 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	int	cleanup(t_scene *scene, char *msg)
{
	ft_putstr_fd(msg, 2);
	free_objects(scene->objects);
	scene->objects = NULL;
	return (1);
}

static	int	setup_window(t_scene *scene, t_mlx *mlx)
{
	scene->width = WINDOW_WIDTH;
	scene->height = WINDOW_HEIGHT;
	camera_init(&scene->camera);
	if (!mlx_app_init(mlx, scene->width, scene->height))
	{
		free_objects(scene->objects);
		scene->objects = NULL;
		ft_putstr_fd("Error\nCould not initialise MiniLibX\n", 2);
		return (0);
	}
	mlx->objects = scene->objects;
	render(scene, mlx);
	mlx_loop(mlx->connection);
	return (1);
}

int	main(int ac, char **av)
{
	t_scene	scene;
	t_mlx	mlx;

	if (ac != 2)
	{
		printf("Usage: %s scene.rt\n", av[0]);
		return (1);
	}
	ft_bzero(&scene, sizeof(scene));
	ft_bzero(&mlx, sizeof(mlx));
	if (!parse_scene(av[1], &scene))
		return (cleanup(&scene, "Error\nInvalid scene file\n"));
	print_scene(&scene);
	if (!scene.has_camera || !scene.objects)
		return (cleanup(&scene, "Error\nScene needs a camera and object\n"));
	if (!setup_window(&scene, &mlx))
		return (1);
	return (0);
}
