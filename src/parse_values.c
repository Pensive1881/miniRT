#include "minirt.h"
#include <errno.h>
#include <limits.h>

int parse_double(const char *str, double *out)
{
    char    *end;
    double  value;

    if (!str || !*str || !out)
        return (0);
    errno = 0;
    value = strtod(str, &end);
    if (str == end || *end != '\0' || errno == ERANGE || !isfinite(value))
        return (0);
    *out = value;
    return (1);
}

int parse_int(const char *str, int *out)
{
    char    *end;
    long    value;

    if (!str || !*str || !out)
        return (0);
    errno = 0;
    value = strtol(str, &end, 10);
    if (str == end || *end != '\0' || errno == ERANGE
                   || value < INT_MIN || value > INT_MAX)
        return (0);
    *out = (int)value;
    return (1);
}

int parse_vec3(const char *str, t_vec3 *out)
{
    char    tmp[128];
    char    *first;
    char    *second;
    t_vec3  value;

    if (!str || !out || ft_strlen(str) >= sizeof(tmp))
        return (0);
    ft_strlcpy(tmp, str, sizeof(tmp));
    first = ft_strchr(tmp, ',');
    if (!first)
        return (0);
    second = ft_strchr(first + 1, ',');
    if (!second || ft_strchr(second + 1, ','))
        return (0);
    *first = '\0';
    *second = '\0';
    if (!parse_double(tmp, &value.x) || !parse_double(first + 1, &value.y)
                                     || !parse_double(second + 1, &value.z))
        return (0);
    *out = value;
    return (1);
}

int parse_color(const char *str, t_color *out)
{
    char    tmp[128];
    char    *first;
    char    *second;
    t_color value;

    if (!str || !out || ft_strlen(str) >= sizeof(tmp))
        return (0);
    ft_strlcpy(tmp, str, sizeof(tmp));
    first = ft_strchr(tmp, ',');
    if (!first)
        return (0);
    second = ft_strchr(first + 1, ',');
    if (!second || ft_strchr(second + 1, ','))
        return (0);
    *first = '\0';
    *second = '\0';
    if (!parse_int(tmp, &value.r) || !parse_int(first + 1, &value.g)
                                  || !parse_int(second + 1, &value.b))
        return (0);
    if (value.r < 0 || value.r > 255
        || value.g < 0 || value.g > 255
        || value.b < 0 || value.b > 255)
        return (0);
    *out = value;
    return (1);
}