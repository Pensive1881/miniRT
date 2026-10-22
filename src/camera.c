/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:36:38 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/22 14:57:10 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//we will call this to build right and up from direction, after parsing
//line 24: if camera points straight up we need diffrent world up

void	camera_init(t_camera *cam)
{
	t_vec3	world_up;

	cam->direction = vec3_norm(cam->direction);
	world_up = vec3(0, 1, 0);
	if (fabs(vec3_dot(cam->direction, world_up)) > 0.999)
		world_up = vec3(0, 0, 1);
	cam->right = vec3_norm(vec3_cross(cam->direction, world_up));
	cam->up = vec3_norm(vec3_cross(cam->right, cam->direction));
}

static	t_vec3	pixel_to_dir(t_camera *cam, t_px px)
{
	double	half_w;
	double	u;
	double	v;
	t_vec3	dir;
	t_vec3	aa;

	half_w = tan(cam->fov * M_PI / 360.0);
	u = half_w * (2.0 * (px.x + 0.5) / px.width - 1.0);
	v = half_w / ((double)px.width / px.height)
		* (1.0 - 2.0 * (px.y + 0.5) / px.height);
	aa = vec3_scale(cam->right, u);
	dir = vec3_add(cam->direction,
			vec3_add(aa, vec3_scale(cam->up, v)));
	return (vec3_norm(dir));
}

//one ray per pixel, we will call it in render loop
t_ray	get_ray(t_camera *cam, t_px px)
{
	t_ray	ray;

	ray.origin = cam->position;
	ray.dir = pixel_to_dir(cam, px);
	return (ray);
}
