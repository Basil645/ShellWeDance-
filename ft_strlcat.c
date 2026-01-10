/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 18:20:50 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/09 16:39:05 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <bsd/string.h>
#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	u;
	size_t	dslen;

	u = 0;
	i = ft_strlen(dst);
	if (i >= size)
		return (size + ft_strlen(src));
	dslen = i;
	while (i + 1 < size && src[u])
		dst[i++] = src[u++];
	dst[i] = '\0';
	return (dslen + ft_strlen(src));
}

/*int main()
{
    char dst[8] = "hello";
    char src[] = "srcyr";
    printf("%ld:%s\n", strlcat(dst,src,4),dst);
    printf("%ld:%s\n", ft_strlcat(dst,src,4),dst);
    printf("%ld:%s\n", strlcat(dst,src,5),dst);
    printf("%ld:%s\n", ft_strlcat(dst,src,5),dst);
     printf("%ld:%s\n", ft_strlcat(dst,src,7),dst);
    return 0;
}*/
