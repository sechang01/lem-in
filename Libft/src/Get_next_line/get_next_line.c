/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:51:00 by sechang           #+#    #+#             */
/*   Updated: 2018/09/20 18:02:12 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	nodemem(t_gnl *mem, t_gnl **memo, int fd)
{
	if (mem)
	{
		mem->fd = fd;
		mem->x = -2;
		mem->next = NULL;
		mem->store = (char *)ft_memalloc(sizeof(char) * BUF_SIZE + 1);
		mem->tmp = NULL;
	}
	if (memo)
	{
		(*memo)->fd = fd;
		(*memo)->x = -2;
		(*memo)->next = NULL;
		(*memo)->store = (char *)ft_memalloc(sizeof(char) * BUF_SIZE + 1);
		(*memo)->tmp = NULL;
	}
}

t_gnl	*fdcheck(t_gnl **gnl, int fd)
{
	t_gnl			*i;
	t_gnl			*new;

	if (*gnl == NULL)
	{
		*gnl = (t_gnl *)ft_memalloc(sizeof(t_gnl));
		nodemem(0, gnl, fd);
		return (*gnl);
	}
	i = *gnl;
	while (i->fd != fd)
	{
		if (!(i->next))
		{
			if (!(new = (t_gnl *)ft_memalloc(sizeof(t_gnl))))
				return (NULL);
			i->next = new;
			nodemem(new, 0, fd);
			return (new);
		}
		i = i->next;
	}
	return (i);
}

char	*expandstr(char *line)
{
	char			*tmp;

	tmp = ft_strdup(line);
	free(line);
	if (!(line = (char *)ft_memalloc(sizeof(char) * BUF_SIZE + \
					ft_strlen(tmp) + 1)))
		return (NULL);
	ft_strcpy(line, tmp);
	free(tmp);
	return (line);
}

int		ret_and_store(char *stuf, t_gnl *pgnl, char *line, int j)
{
	int				i;

	i = 0;
	while (stuf[i])
	{
		line[j++] = (stuf[i++] == '\n') ? '\0' : stuf[i - 1];
		if (stuf[i - 1] == '\n')
		{
			pgnl->tmp = ft_strdup(stuf + i);
			free(pgnl->store);
			pgnl->store = ft_strdup(pgnl->tmp);
			free(pgnl->tmp);
			pgnl->x = -1;
			break ;
		}
	}
	if (pgnl->x != -1)
	{
		pgnl->store[0] = '\0';
		pgnl->x = -3;
	}
	line[j] = '\0';
	return (j);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*gnl;
	t_gnl			*pgnl;
	char			buf[BUF_SIZE + 1];
	int				j;

	pgnl = fdcheck(&gnl, fd);
	if ((!(j = 0)) && (fd < 0 || !line || (read(fd, buf, 0) < 0 || BUF_SIZE \
		< 1) || (!(*line = (char *)ft_memalloc(sizeof(char) * BUF_SIZE + 1 + \
					ft_strlen(pgnl->store))))))
		return (-1);
	if (((!(pgnl->x = -2)) && pgnl->store[0]))
		j = ret_and_store(pgnl->store, pgnl, *line, j);
	if (pgnl->x == -1)
		return (1);
	while (!(pgnl->store[0]) && (pgnl->x = read(fd, buf, BUF_SIZE)))
	{
		buf[pgnl->x] = '\0';
		j = ret_and_store(buf, pgnl, *line, j);
		if (pgnl->x == -3)
			*line = expandstr(*line);
		else
			break ;
	}
	return ((*line[0]) || pgnl->x == -1) ? (1) : (0);
}
