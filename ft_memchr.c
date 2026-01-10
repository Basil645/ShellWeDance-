/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:54:48 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/10 21:10:15 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
//#include <string.h>

void	*ft_memchr(const void *s, int value, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < size)
	{
		if (ptr[i] == (unsigned char)value)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

/*int main()
{
//char myStr[] = "Hello World!";
 // char *myPtr = (char*)memchr(myStr, 'o', 12);
  int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
		printf("%s", (char *)ft_memchr(tab, -1, 7));
//  if (myPtr != NULL) {
   // printf("%s", myPtr);
 // }
  return 0;
}*/
