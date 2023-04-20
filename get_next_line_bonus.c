/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrabajo <gtrabajo@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 02:04:52 by gtrabajo          #+#    #+#             */
/*   Updated: 2023/04/20 02:09:37 by gtrabajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char		*buff[1024];
	int				i;
	int				j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buff[fd] == NULL)
		buff[fd] = ft_strdup("");
	buff[fd] = ft_reading(fd, buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	i = ft_line_size(buff[fd]);
	if (buff[fd][i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (line == NULL)
		return (NULL);
	j = -1;
	while (++j < i)
		line[j] = buff[fd][j];
	line[j] = '\0';
	buff[fd] = ft_update_remaining(buff[fd]);
	return (line);
}
