/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:18:32 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 15:13:59 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

/*char    *ft_strdup(const char *s);
#include <stdio.h>
int main()
{
	char *c;
	char *s = "hello";
	c = ft_strdup(s);
	printf("%s",c);
}*/

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	int		length;
	char	*c;

	length = 0;
	while (s[length])
		length++;
	c = malloc(length + 1);
	if (!c)
		return (NULL);
	c = ft_strcpy(c, s);
	return (c);
}
