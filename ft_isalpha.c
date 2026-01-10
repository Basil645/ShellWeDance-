/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:29:59 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/05 14:40:56 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>

int ft_isalpha(int c);

int main()
{
	printf("%d\n",isalpha('G'));
      	printf("%d\n",ft_isalpha('G'));
	printf("%d\n",isalpha('b'));
        printf("%d\n",ft_isalpha('b'));
	printf("%d\n",isalpha('z'));
        printf("%d\n",ft_isalpha('z'));
	printf("%d\n",isalpha('a'));
	printf("%d\n",ft_isalpha('a'));
	printf("%d\n",isalpha('4'));
	printf("%d\n",ft_isalpha('4'));
	printf("%d\n",isalpha('@'));
	printf("%d\n",ft_isalpha('@'));
}*/

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}
