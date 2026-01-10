/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:23:00 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 20:06:38 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}

/*int main()
{
printf("%d:%d\n",memcmp("abcz","abca",4),ft_memcmp("abcz","abca",4));
//printf("%d:%d",memcmp("abcdefghij", "abcdefgxyz", 7),
//ft_memcmp("abcdefghij", "abcdefgxyz", 7));
}*/
