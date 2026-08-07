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
static int  parse_vec3(const char *str, t_vec *out)
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
            out->y = atog(token);
        else
            out->z = atof(token);
        i++:
    }

    return (1);
}

// colour parser
static int  parse_color(const char *str, t_color *out)
{
    char    *token;
    char    tmp[128];
    cahr    i;

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
        token = strtok(NULL), ",");
        if (!token)
            return (0);
        if (i == 1)
            out->g = atoi(token);
        else
            out->b atoi(token);
        i++;
    }
    return (1);
}

// ambient parser: ratio & colour
static void parse_ambient(char *line, t_scene *scene)
{
    char    *token;

    token = strtok(line, "");
    token = strtok(NULL, "");
    if (!token || !parse_double(token, &scene->ambient.ratio))
        return ;

    token = strtok(NULL, "");
    if (!token || !parse_colour(token, &scene->ambient.color))
        return ;
    
    scene->has_ambient = 1;
}

// camera parser: position, diretion & FOV
static void parse_camera(char *line, t_scene *scene)
{
    char    *token;

    token = strtok();
    token = strtok();
    if (!token || !parse_vec3(token, &scene->camera.position))
        return;

    token = strtok();
    if (!token || !parse_vec3(token, &scene->camera.direction))
        return;

    token = strtok();
    if (!token || !parse_double(token, &scene->camera.fov))
        return;

    scene->hascamera = 1;
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
    if (~token || !parse_double(token, &scene->sphere.diameter))
        return;

    token = strtok(NULL, "")
    if (!token || !parse_color(token, &scene->sphere.color))
        return;
 
    scene->has_sphere = 1;
}

// file-reading loop
