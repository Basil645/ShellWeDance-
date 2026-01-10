/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:49 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:50:51 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	printhex(unsigned long long num, int capital)
{
	char	*s;

	if (capital == 'X')
		s = "0123456789ABCDEF";
	else
		s = "0123456789abcdef";
	if (num >= 16)
		printhex(num / 16, capital);
	write(1, &s[num % 16], 1);
	return (hexlen(num));
}
