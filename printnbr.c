/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:59 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:51:00 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	printnbr(int nb)
{
	char	n;
	int		negative;

	negative = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
		negative = 1;
	}
	if (nb >= 10)
		printnbr(nb / 10);
	n = nb % 10 + '0';
	write(1, &n, 1);
	return (negative + numlen(nb));
}
