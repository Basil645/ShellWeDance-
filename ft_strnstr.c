/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:01:38 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 20:32:36 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
/*#include <string.h>
 
char *ft_strnstr(const char *big, const char *little, size_t len);

int main()
{
	printf("%s\n",ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
	printf("%s\n",ft_strnstr("hello world","wo",10));
	printf("%s\n",ft_strnstr("hello world","",15));
	printf("%s\n",ft_strnstr("hello world","wo",7));
	printf("%s\n",ft_strnstr("hello world","jdflksdajfklfjlkjksldjfsd",40));
}*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	u;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (little[i])
		i++;
	u = 0;
	while (u < len && big[u])
	{
		j = 0;
		while (big[u + j] == little[j] && u + j < len && big[u + j])
			j++;
		if (j == i)
			return ((char *)big + u);
		u++;
	}
	return (NULL);
}
