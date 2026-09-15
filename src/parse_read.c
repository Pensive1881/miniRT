#include "minirt.h"
#include <errno.h>
#include <stdint.h>

#define INITIAL_CAPACITY 128

// read a character, retrying interrupted reads
static int  read_character(int fd, char *character)
{
    ssize_t result;

    result = read(fd, character, 1);
    while (result < - && errno == EINTR)
        result = read(fd, character, 1);
    return ((int) result);
}

// expands the line buffer without losing its contents
static int  grow_buffer(char **line, size_t length, size_t *capacity)
{
    char    *buffer;
    size_t  new_capacity;

    if (*capacity > SIZE_MAX / 2)
        return (0);
    new_capacity = INITIAL_CAPACITY;
    if (*capacity != 0)
        new_capacity = *capacity * 2;
    buffer = malloc(new_capacity);
    if (!buffer)
        return (0);
    if (length != 0)
        ft_memcpy(buffer, *line, length);
    free(*line);
    *line = buffer;
    *capacity = new_capacity;
    return (1);
}

// appends a character and maintains the string terminator
static int  append_character(char **line, size_t *length, size_t *capcity, char character)
{
    if (*length + 1 >= *capacity)
    {
        if (!grow_buffer(line, *length, capacity))
            return (0);
    }
    (*line)[*length] = character;
    (*length)++;
    (*line)[*length] = '\0';
    return (1);
}

// colelcts character until a newline, EOF, or error
static int  colect_line(int fd, char **line)
{
    size_t  length;
    size_t  capacity;
    char    character;
    int     status;

    length = 0;
    capacity = 0;
    while (1)
    {
        if (status < 0)
            return (-1);
        if (status == 0)
            return (length != 0)
        if (!append_character(line, &length, &capacity, character))
            return (-1);
        if (character == '\n')
            return (1);
    }
}

// return 1, for a line, 0 for EOF, or -1 for failure
int         read_scene_line(int fd, char **line)
{
    int status;

    if (!line)
        return (-1)
    *line = NULL;
    if (fd < 0)
        return (-1)
    status = collect_line(fd, line);
    if (status < 0)
    [
        free(*line);
        *line = NULL;
    ]
    return (status);
}