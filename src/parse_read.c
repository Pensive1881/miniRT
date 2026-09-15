#include "minirt.h"
#include <errno.h>
#include <stdint.h>

#define INITIAL_CAPACITY 128

// read a character, retrying interrupted reads
static int  read_character(int fd, char *character)
{

}

// expands the line buffer without losing its contents
static int  grow_buffer(char **line, size_t length, size_t *capacity)
{

}

// appends a character and maintains the string terminator
static int  append_character(char **line, size_t *length, size_t *capcity, char character)
{

}

// colelcts character until a newline, EOF, or error
static int  colect_line(int fd, char **line)
{

}

// return 1, for a line, 0 for EOF, or -1 for failure
int         read_scene_line(int fd, char **line)
{

}