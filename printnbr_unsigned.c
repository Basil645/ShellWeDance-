/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnbr_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:51:09 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:51:10 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	printnbr_unsigned(unsigned int nb)
{
	char	n;

	if (nb >= 10)
		printnbr_unsigned(nb / 10);
	n = nb % 10 + '0';
	write(1, &n, 1);
	return (numlen(nb));
}
