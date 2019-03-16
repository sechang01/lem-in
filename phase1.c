/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:33:55 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:41:46 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ants_in(t_lemin *input, int k, char *line)
{
	if (k <= 0)
		return (-1);
	else if ((input->ants_in = ft_atoi(line)))
	{
		ft_printf("%d\n", input->ants_in);
		input->g++;
		return (1);
	}
	else
		return (-1);
}

void		split(t_lemin *input, t_rooms *tmp, t_links *lks, char **splitee)
{
	tmp->dist = -1;
	tmp->occupied = 0;
	if (input->startend == 1 && (ft_printf("##start\n")))
	{
		tmp->occupied = 1;
		input->start = tmp;
	}
	else if (input->startend == 2 && (ft_printf("##end\n")))
	{
		tmp->dist = 0;
		input->end = tmp;
	}
	tmp->name = ft_strdup(splitee[0]);
	if (ft_strrchr(tmp->name, '-') || ft_strrchr(tmp->name, 'L'))
		error_exit(1);
	tmp->x = ft_atoi(splitee[1]);
	tmp->y = ft_atoi(splitee[2]);
	ft_printf("%s %d %d\n", tmp->name, tmp->x, tmp->y);
	tmp->linx = NULL;
	tmp->next = input->roomhead;
	input->roomhead = tmp;
	if (!(hash_install(splitee[0], tmp, input->hasht)))
		return ;
	input->nbrofrooms++;
}

static int	initb(t_rooms *tmp)
{
	tmp->name = NULL;
	tmp->x = '\0';
	tmp->y = '\0';
	tmp->linx = NULL;
	tmp->dist = '\0';
	tmp->occupied = '\0';
	tmp->next = NULL;
	return (1);
}

int			rooms(t_lemin *input, int k, char *line)
{
	t_rooms *tmp;
	t_links *lks;

	if (k <= 0 || (!(tmp = malloc(sizeof(t_rooms)))) || !initb(tmp))
		return (-1);
	else if (line[0] == '#')
	{
		if (!(ft_strcmp(line, "##start")))
			input->startend = 1;
		else if (!(ft_strcmp(line, "##end")))
			input->startend = 2;
	}
	else
	{
		if ((input->ro = (lm_strsplit(line, ' ', 3))))
		{
			split(input, tmp, lks, input->ro);
			input->startend = 0;
		}
		else if (ft_strrchr(line, '-') && (input->g++))
			g_process[input->g].f(input, k, line);
		else
			error_exit(1);
	}
	return (0);
}
