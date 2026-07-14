/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasper <acasper@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:19:39 by acasper           #+#    #+#             */
/*   Updated: 2025/05/19 00:12:50 by acasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1 = s1;
	const unsigned char	*ptr2 = s2;

	while (n--)
	{
		if (*ptr1 != *ptr2)
			return (ptr1 - ptr2);
		ptr1++;
		ptr2++;
	}
	return (0);
}

/*
int	main(void)
{
		return (0);
}
*/
