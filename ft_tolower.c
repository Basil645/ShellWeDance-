/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:13:41 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/06 19:16:35 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>

int ft_tolower(int c);

int main()
{
	printf("%c\n",tolower(100));
	printf("%c\n",ft_tolower(100));
	printf("%c\n",tolower(74));
	printf("%c\n",ft_tolower(74));
	printf("%c\n",tolower(10));
	printf("%c\n",ft_tolower(10));
}*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}
