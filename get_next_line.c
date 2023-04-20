/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrabajo <gtrabajo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:54:39 by gtrabajo          #+#    #+#             */
/*   Updated: 2023/04/20 02:27:18 by gtrabajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_line_size(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	return (i);
}

char	*ft_update_remaining(char *buff)
{
	char	*remaining;
	char	*aux;

	aux = ft_strchr(buff, '\n');
	if (aux == NULL)
	{
		free(buff);
		return (NULL);
	}
	remaining = ft_strdup(aux + 1);
	free(buff);
	return (remaining);
}

char	*ft_reading(int fd, char *buff)
{
	char	*aux;
	int		rbytes;

	aux = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (aux == NULL)
		return (NULL);
	rbytes = 1;
	while (rbytes > 0 && ft_strchr(buff, '\n') == NULL)
	{	
		rbytes = read(fd, aux, BUFFER_SIZE);
		if (rbytes < 0)
			break ;
		aux[rbytes] = '\0';
		buff = ft_strjoin(buff, aux);
	}
	free(aux);
	if (ft_strlen(buff) == 0 || rbytes < 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*buff;
	int				i;
	int				j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buff == NULL)
		buff = ft_strdup("");
	buff = ft_reading(fd, buff);
	if (buff == NULL)
		return (NULL);
	i = ft_line_size(buff);
	if (buff[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = buff[j];
	line[j] = '\0';
	buff = ft_update_remaining(buff);
	return (line);
}
