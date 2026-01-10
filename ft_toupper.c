/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 18:57:21 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/09 16:32:38 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>

int ft_toupper(int c);

int main()
{
	printf("%c\n",toupper(100));
	printf("%c\n",ft_toupper(100));
	printf("%c\n",toupper(74));
	printf("%c\n",ft_toupper(74));
	printf("%c\n",toupper(10));
	printf("%c\n",ft_toupper(10));
}*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}
