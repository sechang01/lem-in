/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:33:55 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 02:00:19 by sechang          ###   ########.fr       */
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

static int	initb(t_rooms *tmp)
{
	tmp->name = NULL;
	tmp->x = '\0';
	tmp->y = '\0';
	tmp->linx = NULL;
//	tmp->crossed = NULL;
	tmp->dist = '\0';
	tmp->occupied = '\0';
	tmp->next = NULL;
//	tmp->intent = NULL;
//	tmp->p_me = NULL;
//	tmp->collision = NULL;
//	tmp->dist_diff = 0;
//	tmp->stuck = 0;
//	tmp->male = 0;
//	tmp->female = 0;
//	tmp->begin_path = NULL;
//	tmp->counter = 0;
	tmp->pathnbr = 0;
	tmp->bfs = 0;
	return (1);
}

void		split(t_lemin *input, t_rooms *tmp, t_links *lks, char **splitee)
{
	tmp->dist = 999999999;
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
	if (ft_strrchr(tmp->name, '-') || ft_strrchr(tmp->name, 'L') || ft_strrchr(tmp->name, '#'))
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

static void	commands_comments(t_lemin *input, char *line)
{
	if ((ft_strstr(line, "#Here is the number of lines required:")))
		input->best_turn = ft_atoi(line + 38);
	if (!(ft_strcmp(line, "##start")))
		input->startend = 1;
	else if (!(ft_strcmp(line, "##end")))
		input->startend = 2;
	else
		ft_printf("%s\n", line);
}

int			rooms(t_lemin *input, int k, char *line)
{
	t_rooms *tmp;
	t_links *lks;

	if (k <= 0)
		return (-1);
	if (line[0] == '#')
		commands_comments(input, line);
	else
	{
		if ((input->ro = (lm_strsplit(line, ' ', 3))))
		{
			if ((!(tmp = malloc(sizeof(t_rooms)))) || !initb(tmp))
				error_exit(1);
			split(input, tmp, lks, input->ro);
			input->startend = 0;
			ft_strsplitdel(&input->ro);
		}
		else if (ft_strrchr(line, '-') && (input->g++))
			g_process[input->g].f(input, k, line);
		else
			error_exit(1);
	}
	return (0);
}
