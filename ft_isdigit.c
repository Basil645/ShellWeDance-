/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:43:56 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/05 16:11:50 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <ctype.h>

int ft_isdigit(int c);

	int main()
{
printf("%d\n", isdigit('9'));
printf("%d\n", ft_isdigit('9'));
printf("%d\n", isdigit('d'));
printf("%d\n", ft_isdigit('d'));	
}*/

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
