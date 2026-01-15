/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:05:59 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/27 17:59:04 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	strjoin_copy(char *dest, const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
}

char	*ft_strjoin_(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	strjoin_copy(result, s1, s2);
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (result);
}
