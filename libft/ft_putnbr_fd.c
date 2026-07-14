/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acasper <acasper@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:55:16 by acasper           #+#    #+#             */
/*   Updated: 2025/06/03 18:02:00 by acasper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n < 10)
	{
		str = n + '0';
		write(fd, &str, 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	str = (n % 10) + '0';
	write(fd, &str, 1);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("424242:\n");
	ft_putnbr_fd(424242, 1);
		write (1, "\n\n", 2);
		printf("-424242:\n");
		ft_putnbr_fd(-424242, 1);
		write (1, "\n\n", 2);
	printf("0:\n");
		ft_putnbr_fd(0, 1);
		write (1, "\n\n", 2);
	printf("-2147483648:\n");
		ft_putnbr_fd(-2147483648, 1);
		write (1, "\n\n", 2);
	printf("2147483647:\n");
		ft_putnbr_fd(2147483647, 1);
		write (1, "\n", 1);
	return (0);
}
*/
