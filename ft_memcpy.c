/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:15:03 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 19:59:02 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		dest++;
		src++;
		i++;
	}
	return (dest - i);
}

/*int main()
{
//	char a[5] = "sssss";
	char b[30] = "jjjjjjjjjjjjjjjjjjjjjjj";
	ft_memcpy(&b,"zyxwvutsrqponmlkjihgfedcba",14);
	printf("%s",b);
	}*/
