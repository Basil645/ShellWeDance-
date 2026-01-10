/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:12:29 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/07 15:14:52 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>

int ft_isalnum(int c);
int main()
{
	printf("%d\n", isalnum(5));
	printf("%d\n", ft_isalnum(5));
	 printf("%d\n", isalnum('a'));
        printf("%d\n", ft_isalnum('a'));

}*/

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (8);
	return (0);
}
