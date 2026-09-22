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
    t_object    *object;

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
    object = create_object(SPHERE, value.color);
    if (!object)
        return (0);
    object->sp = value;
    add_object(scene, object);
    scene->sphere = value;
    scene->has_sphere = 1;
    return (1);
}

// parses the plane values
int parse_plane(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_vec3      point;
    t_vec3      normal;
    t_color     color;
    t_object    *object;

    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &point))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &normal))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_color(token, &color))
        return (0);
    if (next_token(&cursor) || !valid_orientation(normal))
        return (0);
    object = create_object(PLANE, color);
    if (!object)
        return (0);
    object->pl.point = point;
    object->pl.normal = normal;
    add_object(scene, object);
    return (1);
}

// parses the cylinder values
int parse_cylinder(char *line, t_scene *scene)
{
    char        *cursor;
    char        *token;
    t_vec3      center;
    t_vec3      axis;
    t_color     color;
    double      diameter;
    double      height;
    t_object    *object;

    cursor = line;
    token = next_token(&cursor);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &center))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_vec3(token, &axis))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_double(token, &diameter))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_double(token, &height))
        return (0);
    token = next_token(&cursor);
    if (!token || !parse_color(token, &color))
        return (0);
    if (next_token(&cursor) || !valid_orientation(axis
            || diameter < 0.0 || height <= 0.0))
        return (0);
    object = create_object(CYLINDER, color);
    if (!object)
        return (0);
    object->cy.center = center;
    object->cy.axis = axis;
    object->cy.radius = diameter / 2.0;
    object->cy.height = height;
    add_object(scene, object);
    return (1);
}