/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:54:07 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/09 16:39:48 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
/*#include <string.h>
size_t ft_strlen(const char *s);
int main()
{
    printf("%ld\n",ft_strlen("hello"));
    printf("%ld\n",strlen("hello"));
    printf("%ld\n",ft_strlen(""));
    printf("%ld\n",strlen(""));
    return 0;
}*/

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}
