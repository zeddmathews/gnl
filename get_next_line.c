/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmathews <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 18:13:09 by zmathews          #+#    #+#             */
/*   Updated: 2019/07/22 18:13:40 by zmathews         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

static char		*add_to_array(char *lines, char *buf)
{
	char *new;

	if (!lines || !buf)
		return (NULL);
	new = ft_strjoin(lines, buf);
	if (!new)
		return (NULL);
	ft_strdel(&lines);
	return (new);
}

static char		*get_line(char **line, char *lines)
{
	char	*temp;
	int		i;

	i = 0;
	while (lines[i] != '\n' && lines[i] != '\0')
		i++;
	*line = ft_strsub(lines, 0, i);
	if (ft_strcmp(*line, lines) == 0)
	{
		temp = NULL;
		lines = NULL;
	}
	else
	{
		temp = ft_strsub(lines, i + 1, (ft_strlen(lines + i) + 1));
		ft_strdel(&lines);
	}
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];
	static char	*lines[MAX_FD];
	int			ret;

	if (fd < 0 || fd > MAX_FD || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if (!lines[fd])
		lines[fd] = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		lines[fd] = add_to_array(lines[fd], buf);
		if (ft_strchr(lines[fd], '\n'))
			break ;
	}
	if (ret < BUFF_SIZE && !ft_strlen(lines[fd]))
		return (0);
	lines[fd] = get_line(line, lines[fd]);
	return (1);
}
