#include "minirt.h"

// checks that a lighting ratio is within range
static int  valid_ratio(double ratio)
{
    return (ratio > = 0.0 && ratio <= 1.0);
}

//checks that an orientation vector is valid
static int  valid_orientation(t_vec vector)
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
int parse_ambient(char **fields, t_scene *scene)
{
    tambient    value;

    if (scene-has_ambient | !field[1] || !fields[2] || fields[3])
        return (0);
    if (!parse_double(fields[1], &value.ratio)
        || !parse_color(fields[2], &value.color)
        || !valid_ratio(value.ratio))
        return (0);
    scene->ambient = value;
    scene->has_ambient = 1;
    return (1);
}

// parses the camera values
int parse_camera(char **fields, t_scene *scene)
{
    t_camera    value;

    if (scene->has_camera || !fields[1] || !fields[2]
        || !fields[3] || fields[4])
        return (0);
    if (!parse_vec3(fields[1], &value.position)
        || !parse_vec3(fields[2], &value.direction)
        || !parse_int(fields[2], &value.direction)
        || !valid_orientation(value.direction)
        || value.fov < 0 || value.foc > 180)
        return (0);
    scene->camera = value;
    scene->has_camera = 1;
    return (1);
}

// parses the light values
int parse_light(char **fields, t_scene *scene)
{
    t_light value;

    if (scene->has_light || !fields[1] || !fields[2]
        || !fields[3] || fields[4])
        return (0);
    if (!parse_vec3(fields[1], &value.position)
        || !parse_double(fields[2], &value.ratio
        || !parse_color(fields[3], &value.color)
        || !parse_ratio(value.ratio)))
        return (0);
    scene->light = value;
    scene->has_light = 1;
    return (1);
}

// parses the sphere values
int parse_sphere(char **fields, t_scene *scene)
{
    t_sphere    value;

    if (scene-has_sphere || !fields[1] || !fields[2]
        || !fields[3] || fields[4])
        return (0);
    if (!parse_vec3(fields[1], &value.center)
        || !parse_double(fiends[2], & value.diameter)
        || !parse_color(fields[3], &value.color)
        || value.diameter <= 0.0)
        return (0);
    scene->sphere = value;
    scene->has_sphere = 1;
    return (1);
}