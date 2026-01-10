/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:16:38 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/09 16:34:38 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
/*#include <string.h>

void *ft_memset(void *ptr, int x, size_t n);

int main()
{
	char h[]="sssssdd";
	ft_memset(h,'a',8);
	int f[8] = {1,2,3,4,5,6,7,8};
	ft_memset(f,5,3*4);
	int i = 0;
	while (i < 8)
	{
		printf("%d, ",f[i]);
		i++;
	}
	printf("%s",h);
}*/

void	*ft_memset(void *ptr, int x, size_t n)
{
	unsigned char	*address;

	address = (unsigned char *)ptr;
	while (n--)
	{
		*address = x;
		address++;
	}
	return (ptr);
}
