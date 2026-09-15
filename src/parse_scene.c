#include "minirt.h"
#include <fcntl.h>

#define MAX_FIELDS 8

// check whether a character has whitespace
static int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
         || c == '\r' || c == '\v' || c == '\f');
}

// check wheter two strings are equal
static int  str_equal(const char *first, const char *second)
{
    size_t  length;

    if (!first || !second)
        return (0);
    length = ft_strlen(first);
    if (length != ft_strlen(second))
        return (0);
    return (ft_strncmp(first, second, length) == 0);
}

// separates a line into whitespace-delimited fields
static int  split_fields(char *line, char **fields)
{
    int count;

    count = 0;
    while (*line)
    {
        while (*line && is_space(*line))
            line++;
        if (!*line)
            break ;
        if (count >= MAX_FIELDS - 1)
            return (-1);
        fields[count++] = line;
        while (*line && !is_space(*line))
            line++;
        if (*line)
            *line++ = '\0';
    }
    fields[count] = NULL;
    return (count);
}

// sends an element to its matching parser
static int  dispatch_element(char **fields, t_scene *scene)
{
    if (str_equal(fields[0], "A"))
        return (parse_ambient(fields, scene));
    if (str_equal(fields[0], "C"))
        return (parse_camera(fields, scene));
    if (str_equal(fields[0], "L"))
        return (parse_light(fields, scene));
    if (str_equal(fields[0], "sp"))
        return (parse_sphere(fields, scene));
    return (0);
}

// parses one line from the scene file
static int  parse_line(char *line, t_scene *scene)
{
    char    *fields[MAX_FIELDS];
    int     count;

    count = split_fields(line, fields);
    if (count < 0)
        return (0);
    if (count == 0)
        return (1);
    return (dispatch_element(fields, scene));
}

// checks that the filename ends in .rt
static int  valid_extension(const char *filename)
{
    size_t  length;

    if (!filename)
        return (0);
    length = ft_strlen(filename);
    if (length <= 3)
        return (0);
    return (ft_strncmp(filename + length - 3, ".rt", 4) == 0);
}

// checks that all required scene elements were found
static int  scene_is_complete(t_scene *scene)
{
    return (scene->has_ambient
        && scene->has_camera
        && scene->has_light);
}

// reads and parses an entire scene file
int         parse_scene(const char *filename, t_scene *scene)
{
    char    *line;
    int     fd;
    int     status;
    int     valid;

    if (!scene || !valid_extension(filename))
        return (0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    valid = 1;
    status = read_scene_line(fd, &line);
    while (status == 1)
    {
        valid = parse_line(line, scene);
        free(line);
        if (!valid)
            break ;
        status = read_scene_line(fd, &line);
    }
    close(fd);
    return (valid && status == 0 && scene_is_complete(scene));
}