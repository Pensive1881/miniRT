/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasper <acasper@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:06:05 by acasper           #+#    #+#             */
/*   Updated: 2025/06/03 12:46:57 by acasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(char c)
{
	if (c < 48)
		return (0);
	else if (c > 57 && c < 65)
		return (0);
	else if (c > 90 && c < 97)
		return (0);
	else if (c > 122)
		return (0);
	return (1);
}

/*
int     main()
{
        return (0);
}
*/
