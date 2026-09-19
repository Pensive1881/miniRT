#include "minirt.h"
#include <fctl.h>

// skips spaces and tabs before an element
static char *skip_space(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

// sends an element to its matching parser
static int  parse_element(char *line, t_scene *scene)
{
    if (ft_strncmp(line, "A ", 2) == 0)
        return (parse_ambient(line, scene));
    if (ft_strncmp(line, "C ", 2) == 0)
        return (parse_camera(line, scene));
    if (ft_strncmp(line, "L ", 2) == 0)
        return (parse_light(line, scene));
    if (ft_strncmp(line, "sp ", 3) == 0)
        return (parse_sphere(line, scene));
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
    char    *line;
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
    status = read_scene_line(fd, &line);
    while (Status == 1)
    {
        trimmed = skip_space(line);
        if (*trimmed != '\0' && *trimmed != '\n' && *trimmed != '#')
            valid = parse_element(trimmed, scene);
        free(line);
        if (!valid)
            break ;
        status = read_scene_line(fd, &line);
    }
    close(fd);
    return (valid && status == 0);
}