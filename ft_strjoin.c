/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:30:55 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/07 15:53:41 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

/*char *ft_strjoin(char const *s1, char const *s2);
int main()
{
	char *hello = ft_strjoin("hello","world");
	printf("%s", hello);
}*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		u;

	i = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(i + 1);
	i = 0;
	u = 0;
	if (s == NULL)
		return (NULL);
	while (s1[i])
	{
		s[u] = s1[i];
		u++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		s[u] = s2[i];
		u++;
		i++;
	}
	s[u] = '\0';
	return (s);
}
