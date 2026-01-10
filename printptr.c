/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:17 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:51:18 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static int	ptrlen(unsigned long long n)
{
	int	length;

	length = 1;
	while (n >= 16)
	{
		n /= 16;
		length++;
	}
	return (length);
}

int	printptr(unsigned long long num)
{
	if (!num)
		return (printstr("(nil)"));
	printstr("0x");
	printhex(num, 'x');
	return (ptrlen(num) + 2);
}
