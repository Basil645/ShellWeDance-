/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 20:01:05 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/12 20:23:30 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
/*char *ft_substr(char const *s, unsigned int start, size_t len);
int main()
{
	char *s = ft_substr("hello world",6,20);
	printf("%s",s);
	free(s);
}*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*copy;
	int		i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) <= len)
	{
		copy = malloc((int)ft_strlen(s) - start + 1);
		len = ft_strlen(s);
	}
	else
		copy = malloc(len + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (len-- && s[start])
		copy[i++] = s[start++];
	copy[i] = '\0';
	return (copy);
}
