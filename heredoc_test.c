#include "minishell.h"
#include "../get_next_line/get_next_line.h"

int	read_heredoc_data(char *limiter)
{
	char	*line;
	int	fd[2];

	fd[0] = -1;
	pipe(fd); // prot
	line = NULL;
	while (!line || ((ft_strlen(line) - 1) != ft_strlen(limiter) 
			|| ft_strncmp(line, limiter, ft_strlen(limiter))))
	{
		if (line)
			free(line);
		ft_printf(">");
		line = get_next_line(0); // prot
		if (((ft_strlen(line) - 1) != ft_strlen(limiter)
                        || ft_strncmp(line, limiter, ft_strlen(limiter))))
			write(fd[1], line, ft_strlen(line));
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}

void	read_file(int fd)
{
	char buffer[1];

	while (read(fd, buffer, 1))
	{
		printf("%c", buffer[0]);
	}
}

int main()
{
	struct s_heredoc_data *list;
	list = NULL;
	
	int heredoc_fd = read_heredoc_data(("end"));
	read_file(heredoc_fd);
	/*char *line;
	while ((line = get_next_line(heredoc_fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}*/
	close(heredoc_fd);
}
