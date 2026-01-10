/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:48:56 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/11 14:37:23 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
/*#include <string.h>
int ft_strncmp(const char *s1, const char *s2, size_t n);
int main()
{
//	printf("%d\n",strncmp("ff","gg",0));
//	printf("%d\n",ft_strncmp("ff","gg",0));
	printf("%d\n",strncmp("test\200", "test\0", 6));
//	printf("%d\n",ft_strncmp("abcdefgh", "abcdwxyz", 4));
}*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
