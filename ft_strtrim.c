/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:47:12 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/12 13:05:57 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	charexist(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s, char *set)
{
	int		u;
	int		i;
	int		resindex;
	char	*result;

	i = 0;
	if (!s || !set)
		return (NULL);
	while (s[i] && charexist(s[i], set))
		i++;
	u = ft_strlen(s) - 1;
	while (s[u] && charexist(s[u], set))
		u--;
	if (u < i)
		return (ft_strdup(""));
	result = malloc(u - i + 2);
	if (!result)
		return (NULL);
	resindex = 0;
	while (i <= u)
		result[resindex++] = s[i++];
	result[resindex] = '\0';
	return (result);
}

/*int main()
{
    printf("result:\"%s\"\n", ft_strtrim("", "ab"));
printf("result:%s\n", ft_strtrim("ababaaa My name is Simon bbaaabb", "zxy"));
    printf("result:%s\n", ft_strtrim("xyzhelloxyx","zxy"));
      printf("result:\"%s\"\n", ft_strtrim("xyzhelloxyx","zxyhello"));
    return 0;
}*/
