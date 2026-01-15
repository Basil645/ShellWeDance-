/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kal-haj- <kal-haj-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:52:08 by kal-haj-          #+#    #+#             */
/*   Updated: 2025/08/27 17:26:23 by kal-haj-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

char	*get_next_line(int fd);
char	*ft_strjoin_(char *s1, char *s2);
//char	*ft_strdup(const char *s);
//char	*ft_strchr(const char *s, int c);

#endif
