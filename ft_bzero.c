/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:10:27 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/09 13:57:51 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
/*#include <strings.h>

void ft_bzero(void *s, size_t n);

int main()
{

}*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
