/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benmoham <benmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:16:26 by benmoham          #+#    #+#             */
/*   Updated: 2020/01/22 21:39:18 by benmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) *
	(ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

int		boucle(char **stock, int fd, int ret)
{
	char *buff;

	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_strchr(*stock, '\n') && (ret = read(fd, buff, BUFFER_SIZE)))
	{
		buff[ret] = '\0';
		*stock = ft_strjoin_free(*stock, buff);
	}
	free(buff);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char	*stock = NULL;
	int			i;
	char		*tmp;

	ret = 0;
	i = 0;
	if (!line || BUFFER_SIZE < 1 || read(fd, NULL, 0) == -1)
		return (-1);
	if (!stock)
		if (!(stock = calloc(1, 1)))
			return (-1);
	boucle(&stock, fd, ret);
	while (stock[i] && stock[i] != '\n')
		i++;
	tmp = stock;
	*line = ft_substr(stock, 0, i);
	stock = ((stock[i] == '\n') ? ft_strdup(stock + i + 1) : NULL);
	free(tmp);
	return (((stock == NULL) && !ret) ? 0 : 1);
}
