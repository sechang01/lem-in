/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:43:00 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:33:13 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		clearlinks(t_lemin *input, t_rooms *beginlst)
{
	t_rooms		*r_tmp;
	t_rooms		*rr_tmp;

	r_tmp = beginlst;
	while (r_tmp)
	{
		rr_tmp = r_tmp;
		r_tmp = r_tmp->next;
		rr_tmp->next = NULL;
	}
}

void		start_nexus(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;
	static int	i = 0;

	l_tmp = input->start->linx;
	while (l_tmp && i < input->ants_in)
	{
		if ((r_tmp = closest_node(input, input->start, -1, -1)))
		{
			i++;
			if (input->anthead == NULL)
			{
				input->anthead = r_tmp;
				input->anthead->next = NULL;
			}
			else if (input->anttail == NULL)
				input->anttail = r_tmp;
			else
				input->anttail = r_tmp;
			input->prevroom = r_tmp;
		}
		else
			break ;
		l_tmp = l_tmp->next;
	}
}

static void	initc(t_lemin *input)
{
	input->turn = 1;
	input->anthead = NULL;
	input->anttail = NULL;
	input->entrances = 0;
}

static int	gogo_ants2(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_rooms		*rr_tmp;
	t_rooms		*close_tmp;

	if (input->usage != 't')
		ft_printf("\n");
	input->antnum = 1 + input->ants_out;
	r_tmp = input->anthead;
	input->prevroom = NULL;
	while (r_tmp)
	{
		if ((close_tmp = closest_node(input, r_tmp, -1, -1)))
			input->prevroom = close_tmp;
		rr_tmp = r_tmp;
		r_tmp = r_tmp->next;
		if (input->blockstate != 33)
			rr_tmp->next = NULL;
	}
	if (input->anttail)
		input->anttail->next = NULL;
	start_nexus(input);
	if (input->ants_out >= input->ants_in)
		return (1);
	input->turn++;
	return (0);
}

int			gogo_ants(t_lemin *input)
{
	if (input->usage && input->usage != 't')
		usage_flags(input);
	clearlinks(input, input->roomhead);
	initc(input);
	while (input->ants_out < input->ants_in)
	{
		if (gogo_ants2(input))
			break ;
	}
	if (input->usage == 't')
		ft_printf("\n\n\nTURNS: %d\n", input->turn);
	else
		ft_printf("\n");
	return (0);
}
