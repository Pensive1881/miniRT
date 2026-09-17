#include "minirt.h"
#include <errno.h>

// scene initializer: resets the scene to zero
static void init_scene(t_scene *scene)
{
    memset(scene, 0, sizeof(*scene));
}
// debug printer
static void print_scene(const t_scene *scene)
{
    printf("Parsed scene:\n");
    if (scene->has_ambient)
        printf("Ambient: ratio=%.2f color=(%d,%d,%d)\n",
            scene->ambient.ratio,
            scene->ambient.color.r,
            scene->ambient.color.g,
            scene->ambient.color.b);

    if (scene->has_camera)
        printf("Camera: pos=(%.2f,%.2f,%.2f) dir=(%.2f,%.2f,%.2f) fov=%d\n",
            scene->camera.position.x, scene->camera.position.y, scene->camera.position.z,
            scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z,
            scene->camera.fov);

    if (scene->has_light)
        printf("Light: pos=(%.2f,%.2f,%.2f) ratio=%.2f color=(%d,%d,%d)\n",
            scene->light.position.x, scene->light.position.y, scene->light.position.z,
            scene->light.ratio,
            scene->light.color.r,
            scene->light.color.g,
            scene->light.color.b);

    if (scene->has_sphere)
        printf("Sphere: center=(%.2f,%.2f,%.2f) diameter=%.2f color=(%d,%d,%d)\n",
            scene->sphere.center.x, scene->sphere.center.y, scene->sphere.center.z,
            scene->sphere.diameter,
            scene->sphere.color.r,
            scene->sphere.color.g,
            scene->sphere.color.b);
}

int main(int argc, char **argv)
{
    t_scene scene;
    t_mlx   mlx;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s scene.rt\n", argv[0]);
        return (1);
    }

    init_scene(&scene);
    if (!parse_scene(argv[1], &scene))
    {
        fprint(stderr, "Error\nInvalid scene file\n");
        return (1);
    }
    print_scene(&scene);
    if (!scene.has_camera || !scene.has_sphere)
    {
        fprintf(stderr, "Error\nScene needs a camera and sphere\n");
        return (1);
    }
    scene.width = WINDOW_WIDTH;
    scene.height = WINDOW_HEIGHT;
    camera_init(&scene.camera);
    if (!mlx_app_init(&mlx, scene.width, scene.height))
    {
        fprintf(stderr, "Error\nCould not initialize MiniLibX\n");
        return (1);
    }
    render(&scene, &mlx);
    mlx_loop(mlx.connection);

    return (0);
}