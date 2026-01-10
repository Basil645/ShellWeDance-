/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:23:33 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 15:10:52 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*int ft_atoi(const char *nptr);

int main()
{
    printf("%d\n",atoi(" -2g00"));
    printf("%d\n",ft_atoi(" -2g00"));
    printf("%d\n",atoi("\t\r    2147483647"));
    printf("%d\n",ft_atoi("\t\r    9999999999999999999999999999
    999999999999999999999999"));
    printf("%d\n",atoi("  --2fd2"));
    printf("%d\n",ft_atoi("  --2fd2"));
}*/

int	ft_atoi(const char *nptr)
{
	int	number;
	int	i;
	int	negative;

	number = 0;
	i = 0;
	negative = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	if (negative == 1)
		return (number * -1);
	return (number);
}
