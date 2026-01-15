/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:52:01 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/27 19:00:19 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *result)
{
	char	*buffer;
	int		num_byte;

	num_byte = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while ((result == NULL || !ft_strchr(result, '\n')) && num_byte > 0)
	{
		num_byte = read(fd, buffer, BUFFER_SIZE);
		if (num_byte == -1)
		{
			free(result);
			free(buffer);
			return (NULL);
		}
		buffer[num_byte] = '\0';
		result = ft_strjoin_(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*ft_get_line(char *result)
{
	char	*line;
	int		i;

	if (!result || result[0] == '\0')
		return (NULL);
	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (result[i] && result[i] != '\n')
	{
		line[i] = result[i];
		i++;
	}
	if (result[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_result(char *result)
{
	char	*new_result;
	int		i;

	i = 0;
	if (!result)
		return (NULL);
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i])
	{
		free(result);
		return (NULL);
	}
	new_result = ft_strdup(result + i + 1);
	free(result);
	return (new_result);
}

char	*get_next_line(int fd)
{
//	static char	*result;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	/*line = ft_get_line(result);
	result = update_result(result);
	if (!line)
	{
		free(result);
		free(line);
		return (NULL);
	}*/
	return (line);
}
/*
int main(void)
{
	int fd = open("file1.txt", O_RDONLY);
	char *line;

	// line = get_next_line(fd);
	// printf("%s", line);
	// return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
