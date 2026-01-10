/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:24:48 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 20:24:42 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*#include <stdio.h>
char    *ft_itoa(int n);
int main()
{
	printf("%s\n",ft_itoa(-230456));
	printf("%s\n",ft_itoa(2147483647));
	printf("%s\n",ft_itoa(-2147483648));
	printf("%s\n",ft_itoa(0));
	printf("%s\n",ft_itoa(10));
	printf("%s\n",ft_itoa(-10));
}*/

static int	numlen(int n)
{
	int	length;

	length = 1;
	while (n >= 10)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static int	negative(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static char	*handlecases(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return ("");
}

char	*ft_itoa(int n)
{
	int		i;
	int		length;
	int		sign;
	char	*asciinum;

	sign = negative(n);
	if (n == -2147483648 || n == 0)
		return (handlecases(n));
	if (n < 0)
		n *= -1;
	length = numlen(n);
	asciinum = malloc(length + sign + 1);
	if (asciinum == NULL)
		return (NULL);
	i = length + sign - 1;
	if (sign)
		asciinum[0] = '-';
	while (n > 0)
	{
		asciinum[i--] = n % 10 + '0';
		n /= 10;
	}
	asciinum[length + sign] = '\0';
	return (asciinum);
}
