/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase3b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:01:56 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:12:14 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		linkem(t_lemin *input, t_rooms *old, t_rooms *curr, t_rooms *new)
{
	t_rooms		*curr_tmp;
	int			*to;
	int			*tb;

	curr_tmp = curr;
	curr_tmp->occupied = 0;
	new->occupied = 1;
	if (input->thkey == 1)
		input->anthead = new;
	else if (input->thkey == 2)
		input->anttail = new;
	if (input->prevroom && input->prevroom != new)
		input->prevroom->next = new;
}

void		close_end(t_lemin *input, t_rooms *curr)
{
	curr->occupied = 0;
	if (curr == input->anthead)
		input->anthead = curr->next;
	else if (curr == input->anttail)
	{
		if (input->prevroom)
			input->anttail = input->prevroom;
	}
	else
	{
		if (input->prevroom)
			input->prevroom->next = curr->next;
	}
	input->ants_out++;
	if (input->usage != 's')
		ft_printf("L%d-%s ", input->antnum, input->end->name);
}

void		start_path_check(t_lemin *input, t_rooms *curr)
{
	t_links		*l_tmp;
	t_rooms		*h_tmp;
	int			shortest;
	int			numpaths;

	numpaths = 0;
	shortest = 2147483647;
	l_tmp = curr->linx;
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp->dist > 0)
			if ((numpaths++ >= 0) && h_tmp->dist < shortest)
				shortest = h_tmp->dist;
		l_tmp = l_tmp->next;
	}
	l_tmp = curr->linx;
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp->dist > shortest * 2 && (!(input->startpathkey = 0)))
			h_tmp->occupied = 1;
		l_tmp = l_tmp->next;
	}
}

t_rooms		*closest_node2(t_lemin *input, t_rooms *curr)
{
	int			disttmp;
	t_links		*l_tmp;
	t_rooms		*h_tmp;

	disttmp = 2147483647;
	l_tmp = curr->linx;
	input->closest = (curr == input->start) ? NULL : curr;
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp == input->end)
		{
			close_end(input, curr);
			input->antnum++;
			input->closest = NULL;
			break ;
		}
		if (h_tmp->occupied == 0 && h_tmp->dist <= disttmp)
		{
			disttmp = h_tmp->dist;
			input->closest = h_tmp;
		}
		l_tmp = l_tmp->next;
	}
	return (input->closest);
}

t_rooms		*closest_node(t_lemin *input, t_rooms *curr, int hstate, int tstate)
{
	if (curr == input->start && input->startpathkey)
		start_path_check(input, curr);
	hstate = (input->anthead == curr) ? 1 : 0;
	tstate = (input->anttail == curr) ? 1 : 0;
	input->blockstate = 1;
	input->closest = closest_node2(input, curr);
	if (input->closest == curr)
		input->blockstate = 33;
	if (input->closest != curr && input->closest != NULL)
	{
		input->closest->next = curr->next;
		if (hstate == 1 && (input->thkey = 1))
			linkem(input, input->closest->next, curr, input->closest);
		else if (tstate == 1 && (input->thkey = 2))
			linkem(input, input->closest->next, curr, input->closest);
		else
			linkem(input, input->closest->next, curr, input->closest);
		if ((!(input->thkey = 0)) && input->usage != 's')
			ft_printf("L%d-%s ", input->antnum, input->closest->name);
		input->antnum++;
	}
	input->start->occupied = 1;
	input->end->occupied = 0;
	return (input->closest);
}
