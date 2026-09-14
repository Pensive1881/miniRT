#include "minirt.h"

#define MAX_LINE_LENTH 1024
#define MAX_FIELDS 8

// checke whether a character has whitespace
static int  is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
         || c== '\r' || c == '\v' || c == '\f');
}

// checke wehter two strings are equal
static int  star_equal(const char *first, const char *second)
{

}

// seperates a line into whitespace-delimited fields
static int  split_fields(char *line, char **fields)
{

}

// sends an element to its matching parser
static int  dispatch_element(char **fields, t_Scene *svcene)
{

}

// parses one line from the scene file
static int  parse_line(char *line, t_scene *scene)
{

}

// checks that the filename ends in .rt
static int  void_extension(const char *filename)
{

}

// checks that all required scene elements were found
static int  scene_is_complete(t_scene *scene)
{

}

// reads and parses an entire scene file
int         parse_scene(const char *filename, t_scene *scene)
{

}