#include "minirt.h"

// scene initializer: resets the scene to zero
static void init_scene(t_scene *scene)
{
    memset(scene, 0, sizeof(*scene));
}

// number parser
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

// ambient parser
