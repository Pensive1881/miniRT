/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrajni <rrajni@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:38:59 by rrajni            #+#    #+#             */
/*   Updated: 2026/10/23 19:06:37 by rrajni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//#include <float.h>
//#include <limits.h>

static	int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

// parses digits following a decimal point
static	void	parse_fraction(const char **str, double *value, int *has_digit)
{
	double	place;

	place = 0.1;
	(*str)++;
	while (**str >= '0' && **str <= '9')
	{
		*value += (**str - '0') * place;
		place *= 0.1;
		*has_digit = 1;
		(*str)++;
	}
}

// parses a string as a finite double
int	parse_double(const char *str, double *out)
{
	double	value;
	int		sign;
	int		has_digit;

	if (!str || !*str || !out)
		return (0);
	sign = parse_sign(&str);
	value = 0.0;
	has_digit = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (value > (DBL_MAX - (*str - '0')) / 10.0)
			return (0);
		value = value * 10.0 + (*str - '0');
		has_digit = 1;
		str++;
	}
	if (*str == '.')
		parse_fraction(&str, &value, &has_digit);
	if (!has_digit || *str != '\0')
		return (0);
	*out = value * sign;
	return (1);
}

static	int	par_int_di(const char **str, unsigned long *val, unsigned long lim)
{
	unsigned int	digit;

	while (**str >= '0' && **str <= '9')
	{
		digit = (unsigned int)(**str - '0');
		if (*val > (lim - digit) / 10)
			return (0);
		*val = *val * 10 + digit;
		(*str)++;
	}
	return (1);
}

// parses a string as an integer
int	parse_int(const char *str, int *out)
{
	unsigned long	value;
	unsigned long	limit;
	int				sign;

	if (!str || !*str || !out)
		return (0);
	sign = parse_sign(&str);
	if (*str < '0' || *str > '9')
		return (0);
	if (sign < 0)
		limit = (unsigned long)INT_MAX + 1;
	else
		limit = INT_MAX;
	value = 0;
	if (!par_int_di(&str, &value, limit) || *str != '\0')
		return (0);
	if (sign < 0 && value == (unsigned long)INT_MAX + 1)
		*out = INT_MIN;
	else
		*out = (int)value * sign;
	return (1);
}
