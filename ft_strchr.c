/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:28:55 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 20:36:02 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>

char    *ft_strchr(const char *s, int c);

int main()
{
	printf("%s",strchr("fdsfddffdfd aggggggg\n", 'a'));
	printf("%s",ft_strchr("fdsfddffdfd aggggggg\n", 'a'));
	printf("%s",strchr("rrr ddd\n",'a'));
	printf("%s",ft_strchr("rrr ddd\n",'a'));
	printf("%s",strchr("hello",'\0'));
	printf("%s",ft_strchr("hello",'\0'));
}*/

char	*ft_strchr(const char *s, int c)
{
	char	*m;

	m = (char *)s;
	while (*m)
	{
		if (*m == (unsigned char)c)
			return (m);
		else
			m++;
	}
	if (*m == (unsigned char)c)
		return (m);
	return (0);
}
