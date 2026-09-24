#include "minirt.h"
#include <fcntl.h>

#define MAX_SCENE_LINE 1024

// skips spaces and tabs before an element
static char *skip_space(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

// reads one line into a fixed-size buffer
static int  read_scene_line(int fd, char *line, size_t size)
{
    char    character;
    size_t  index;
    ssize_t bytes;

    if (!line || size < 2)
        return (-1);
    index = 0;
    while (index + 1 < size)
    {
        bytes = read(fd, &character, 1);
        if (bytes < 0)
            return (-1);
        if (bytes == 0)
            break ;
        line[index++] = character;
        if (character == '\n')
            break ;
    }
    line[index] = '\0';
    if (index == 0 && bytes == 0)
        return (0);
    if (index + 1 == size && line[index - 1] != '\n')
        return (-1);
    return (1);
}

// sends an element to its matching parser
static int  parse_element(char *line, t_scene *scene)
{
    if (line[0] == 'A' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_ambient(line, scene));
    if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_camera(line, scene));
    if (line[0] == 'L' && (line[1] == ' ' || line[1] == '\t'))
        return (parse_light(line, scene));
    if (ft_strncmp(line, "sp", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return (parse_sphere(line, scene));
    if (ft_strncmp(line, "pl", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return (parse_plane(line, scene));
    if (ft_strncmp(line, "cy", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
        return (parse_cylinder(line, scene));
    return (0);
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

// reads and parses an entire scene file
int parse_scene(const char *filename, t_scene *scene)
{
    char    line[MAX_SCENE_LINE];
    char    *trimmed;
    int     fd;
    int     status;
    int     valid;

    if (!scene || !valid_extension(filename))
        return (0);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (0);
    valid = 1;
    status = read_scene_line(fd, line, sizeof(line));
    while (status == 1)
    {
        trimmed = skip_space(line);
        if (*trimmed != '\0' && *trimmed != '\n' && *trimmed != '#')
            valid = parse_element(trimmed, scene);
        if (!valid)
            break ;
        status = read_scene_line(fd, line, sizeof(line));
    }
    close(fd);
    return (valid && status == 0 && scene->has_ambient && scene->has_camera && scene->has_light);
}