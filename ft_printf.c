/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:49:54 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:49:57 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	printformat(const char *format, va_list list)
{
	if (*format == 'c')
		return (printchar(va_arg(list, int)));
	else if (*format == 's')
		return (printstr(va_arg(list, char *)));
	else if (*format == 'd' || *format == 'i')
		return (printnbr(va_arg(list, int)));
	else if (*format == 'x' || *format == 'X')
		return (printhex(va_arg(list, unsigned int), *format));
	else if (*format == '%')
		return (printchar('%'));
	else if (*format == 'u')
		return (printnbr_unsigned(va_arg(list, unsigned int)));
	else if (*format == 'p')
		return (printptr(va_arg(list, unsigned long long)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		count;
	int		i;

	i = 0;
	if (!format)
		return (-1);
	va_start(list, format);
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += printformat(format + i, list);
		}
		else
			count += printchar(format[i]);
		i++;
	}
	va_end(list);
	return (count);
}
