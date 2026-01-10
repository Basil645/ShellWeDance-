/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:50:08 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/21 14:50:10 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		printchar(char c);
int		printstr(char *s);
int		printnbr(int num);
int		printnbr_unsigned(unsigned int num);
int		printhex(unsigned long long num, int capital);
int		hexlen(unsigned int num);
int		numlen(long long n);
int		printptr(unsigned long long num);

#endif
