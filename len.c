/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:16 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:50:18 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hexlen(unsigned int n)
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

int	numlen(long long n)
{
	int	length;

	length = 1;
	while (n >= 10)
	{
		n /= 10;
		length++;
	}
	return (length);
}
