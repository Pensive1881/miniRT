#include "minirt.h"

// returns the next whitespace-seperated token
static char *next_token(char **cursor)
{
    char    *token;

    if (!cursor || !*cursor)
        return (NULL);

    while (**cursor == ' ' || **cursor == '\t' || **cursor == '\n'
        || **cursor == '\r' || **cursor == '\v' || **cursor == '\f')
        (*cursor)++;
    if (!**cursor)
        return (NULL);
    token = *cursor;
    while (**cursor && **cursor != ' ' && **cursor != '\t'
        && **cursor != '\n' && **cursor != '\r'
        && **cursor != '\v' && **cursor != '\f')
        (*cursor)++;
    if (**cursor)
    {
        **cursor = '\0';
        (*cursor)++;
    }
    return (token);
}

// checks that a lighting ratio is within range
static int  valid_ratio(double ratio)
{
    return (ratio >= 0.0 && ratio <= 1.0);
}

// checks that an orientation vector is valid
static int  valid_orientation(t_vec3 vector)
{
    double length;

    if (vector.x < -1.0 || vector.x > 1.0
        || vector.y < -1.0 || vector.y > 1.0
        || vector.z < -1.0 || vector.z > 1.0)
        return (0);
    length = vec3_len(vector);
    return (length > 0.0);
}

// parses the ambient-light values
int parse_ambient(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_ambient   value;

    if (scene->has_ambient)
        return (0);
    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_double(token, &value.ratio))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_color(token, &value.color))
        return (0);
    if (next_token(&cursor) || !valid_ratio(value.ratio))
        return (0);
    scene->ambient = value;
    scene->has_ambient = 1;
    return (1);
}

// parses the camera values
int parse_camera(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_camera    value;

    if (scene->has_camera)
        return (0);
    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &value.position))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &value.direction))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_int(token, &value.fov))
        return (0);
    if (next_token(&cursor) || !valid_orientation(value.direction)
        || value.fov < 0 || value.fov > 180)
        return (0);
    scene->camera = value;
    scene->has_camera = 1;
    return (1);
}

// parses the light values
int parse_light(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_light     value;

    if (scene->has_light)
        return (0);
    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &value.position))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_double(token, &value.ratio))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_color(token, &value.color))
        return (0);
    if (next_token(&cursor) || !valid_ratio(value.ratio))
        return (0);
    scene->light = value;
    scene->has_light = 1;
    return (1);
}

// parses the sphere values
int parse_sphere(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_sphere    value;

    if (scene->has_sphere)
        return (0);
    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &value.center))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_double(token, &value.diameter))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_color(token, &value.color))
        return (0);
    if (next_token(&cursor) || value.diameter <= 0.0)
        return (0);
    scene->sphere = value;
    scene->has_sphere = 1;
    return (1);
}