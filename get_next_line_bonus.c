/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:55:03 by mohkhan           #+#    #+#             */
/*   Updated: 2024/07/21 10:55:04 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*reader(int fd, char *str, size_t buffer)
{
	char	*res;
	int		bytes_read;

	bytes_read = 1;
	res = (char *)malloc(buffer + 1);
	if (!res)
		return (0);
	while (bytes_read != 0 && !ft_strchr(str, '\n'))
	{
		bytes_read = read(fd, res, buffer);
		if (bytes_read == -1)
			return (free(res), free(str), NULL);
		res[bytes_read] = '\0';
		str = ft_strjoin(str, res);
		if (!str)
			break ;
	}
	if (str && str[0] == '\0')
		return (free(str), free(res), NULL);
	free(res);
	return (str);
}

char	*present_line(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n' && ++i)
		res[i - 1] = str[i - 1];
	res[i] = '\0';
	return (res);
}

char	*next_line(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	res = (char *)malloc(ft_strlen(str) - i + 1);
	if (!res)
		return (NULL);
	i++;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*res;
	int			i;

	i = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd > 1024)
		return (0);
	str[fd] = reader(fd, str[fd], BUFFER_SIZE);
	if (!str[fd])
		return (NULL);
	res = present_line(str[fd]);
	str[fd] = next_line(str[fd]);
	return (res);
}
