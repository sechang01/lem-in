/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 22:22:11 by sechang           #+#    #+#             */
/*   Updated: 2018/09/20 18:01:09 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# define BUF_SIZE 1

typedef struct		s_gnl
{
	char			*store;
	char			*tmp;
	int				x;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
