/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:02:56 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 20:37:44 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>

char    *ft_strrchr(char *s, int c);

int main()
{
	printf("%s\n",strrchr("hello",'l'));
	printf("%s\n",ft_strrchr("hello",'l'));
	printf("%s\n",strrchr("hello",'a'));
	printf("%s\n",ft_strrchr("hello",'a'));
}*/

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		else
			i--;
	}
	return (0);
}
