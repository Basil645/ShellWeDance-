/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:20:49 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/07 13:22:37 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>

int ft_isascii(int c);
int main() {
    printf("%d",isascii(100));
    printf("%d",ft_isascii(100));
    printf("%d",isascii(200));
    printf("%d",ft_isascii(200));
    printf("%d",isascii(0));
    printf("%d",ft_isascii(0));
}*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
