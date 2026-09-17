#include "minirt.h"
#include <fcntl.h>

// skips spaces and tabs before an element
static char *skip_space(chat *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    return (line);
}

// sends an element to its matching parser
static int  parse_element(Char *line, t_scene *scene)
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
    FILE    *file;
    char    line[1024];
    char    *trimmed;
    int     valid;

    if (!scene || !valid_extension(filename))
        return (0);
    file = fopen(filename, "r");
    if (!file)
        return (0);
    valid = 1;
    while (valid && fgets(line, sizeof(line), file))
    {
        trimmed = skip_space(line);
        if (*trimmed != '\0' && *trimmed != '\n' && *trimmed != '#')
            valid = parse_element(trimmed, scene);
    }
    if (ferror(file))
        valid = 0;
    fclose(file);
    return (valid);
}