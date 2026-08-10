#include "minirt.h"

// scene initializer: resets the scene to zero
static void init_scene(t_scene *scene)
{
    memset(scene, 0, sizeof(*scene));
}

// number parser: ratio, diameter & FOV values
static int  parse_double(const char *str, double *out)
{
    char    *end;

    *out = strtod(str, &end);
    return (end != str && *end== '\0');
}

// vector parser: camera positions/directions and sphere centers
static int  parse_vec3(const char *str, t_vec3 *out)
{
    char    *token;
    char    tmp[128];
    int     i;

    if (strlen(str) >= sizeof(tmp))
        return (0);
    strcpy(tmp, str);

    token = strtok(tmp, ",");
    if (!token)
        return (0);
    out->x = atof(token);

    i = 1;
    while (i <=2)
    {
        token = strtok(NULL, ",");
        if (!token)
            return (0);
        if (i == 1)
            out->y = atof(token);
        else
            out->z = atof(token);
        i++;
    }

    return (1);
}

// colour parser
static int  parse_color(const char *str, t_color *out)
{
    char    *token;
    char    tmp[128];
    int    i;

    if (strlen(str) >= sizeof(tmp))
        return (0);
    strcpy(tmp, str);

    token = strtok(tmp, ",");
    if (!token)
        return (0);
    out->r = atoi(token);

    i = 1;
    while (i <=2)
    {
        token = strtok(NULL, ",");
        if (!token)
            return (0);
        if (i == 1)
            out->g = atoi(token);
        else
            out->b = atoi(token);
        i++;
    }
    return (1);
}

// ambient parser: ratio & colour
static void parse_ambient(char *line, t_scene *scene)
{
    char    *token;

    token = strtok(line, " \t\r\n");
    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_double(token, &scene->ambient.ratio))
        return ;

    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_color(token, &scene->ambient.color))
        return ;
    
    scene->has_ambient = 1;
}

// camera parser: position, diretion & FOV
static void parse_camera(char *line, t_scene *scene)
{
    char    *token;

    token = strtok(line, " \t\r\n");
    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_vec3(token, &scene->camera.position))
        return;

    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_vec3(token, &scene->camera.direction))
        return;

    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_double(token, &scene->camera.fov))
        return;

    scene->has_camera = 1;
}

// light parser: position, ratio & colour
static void parse_light(char *line, t_scene *scene)
{
    char    *token;

    token = strtok(line, " \t\r\n");
    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_vec3(token, &scene->light.position))
        return;
    
    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_double(token, &scene->light.ratio))
        return;

    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_color(token, &scene->light.color))
        return;

    scene->has_light = 1;
}

// sphere parser: center, diameter & colour
static void parse_sphere(char *line, t_scene *scene)
{
    char    *token;

    token = strtok(line, " \t\r\n");
    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_vec3(token, &scene->sphere.center))
        return;

    token = strtok(NULL, " \t\r\n");
    if (!token || !parse_double(token, &scene->sphere.diameter))
        return;

    token = strtok(NULL, " \t\r\n")
    if (!token || !parse_color(token, &scene->sphere.color))
        return;
 
    scene->has_sphere = 1;
}

// file-reading loop
static void parse_Scene_file(const char *filename, t_scene *Scene)
{
    FILE    *fp;
    char    line[1024];

    fp = fopen(filename, "r");
    if (!fp)
    {
        perror("fopen");
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char    *trim;

        tri m = line;
        while (*trim == ' ' || *trim == '\t')
            trim++;

        if (*trim == '\0' || *trim == '#')
            continue;

        if (strncmp(trim, "A ", 2) == 0)
            parse_ambient(trim, scene);
        else if (strncmp(trim, "C ", 2) == 0)
            parse_camera(trim, scene);
        else if (strncmp(trim, "L ", 2) == 0)
            parse_light(trim, scene);
        else if (strncmp(trim, "sp ", 3) == 0)
            parse_sphere(trim, scene);
    }

    fclose(fp);
}

// debug printer
static void print_scene(const t_scene *scene)
{
    printf("Parsed scene:\n");
    if (scene->has_ambient)
        printf("Ambient: ratio=%.2f color=(%d,%d,%d)\n",
            scene->ambient.ratio,
            scene->ambient.color.r,
            scene->ambient.color.g
            scene->ambient.color.b);

    if (scene->has_camera)
        printf("Camera: pos=(%.2f,%.2f,%.2f) dir=(%.2f%.2f%.2f) fov=%d\n",
            scene->camera.position.x, scene->camera.position.y, scene->camera.position.z,
            scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z
            scene->camera.camera.fov);

    if (scene->has_light)
        printf("Light: pos=(%.2f,%.2f,%.2f) ratio%.2f color=(%d,%d,%d)\n",
            scene->light.position.x, scene->light.position.y, scene->light.position.z,
            scene->light.ratio,
            scene->light.color.r,
            scene->light.color.g
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

    if (argv != 2)
    {
        fprintf(stderr, "Usage: %s scene.rt\n", argv[0]);
        return (1);
    }

    init_scene(&scene);
    parse_scene_file(argv[1], &scene);
    print_scene(&scene);

    return (0);
}