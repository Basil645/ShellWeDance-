/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahmad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 20:10:20 by bahmad            #+#    #+#             */
/*   Updated: 2025/08/12 14:16:28 by bahmad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	count_words(const char *str, char delimiter)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (str[index])
	{
		while (str[index] == delimiter && str[index])
			index++;
		if (str[index] != delimiter && str[index])
		{
			count++;
			while (str[index] != delimiter && str[index])
				index++;
		}
	}
	return (count);
}

static int	count_chars(const char *str, char delimiter)
{
	int	count;
	int	index;

	count = 0;
	index = 0;
	while (str[index] && str[index] == delimiter)
		index++;
	while (str[index])
	{
		if (str[index] == delimiter)
			break ;
		count++;
		index++;
	}
	return (count);
}

static int	fillrow(char *dest, const char *s, char delimiter)
{
	int	j;

	j = 0;
	while (*s && *s != delimiter)
	{
		dest[j] = *s;
		j++;
		s++;
	}
	dest[j] = '\0';
	return (j);
}

static void	freearray(char **arr, int count)
{
	while (count--)
		free(arr[count]);
	free(arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		i;
	int		rowsnum;

	if (!s)
		return (NULL);
	rowsnum = count_words(s, c);
	i = 0;
	arr = malloc((rowsnum + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[rowsnum] = NULL;
	while (i < rowsnum)
	{
		while (*s && *s == c)
			s++;
		arr[i] = malloc((count_chars(s, c) + 1));
		if (!arr[i])
		{
			freearray(arr, i);
			return (NULL);
		}
		s += fillrow(arr[i++], s, c);
	}
	return (arr);
}
