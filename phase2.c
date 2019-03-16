/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:34:01 by sechang           #+#    #+#             */
/*   Updated: 2019/02/02 16:05:05 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			blockpath(t_lemin *input)
{
	t_rooms		*r_tmp;

	r_tmp = input->roomhead;
	while (r_tmp)
	{
		if (r_tmp->dist == -1)
			r_tmp->occupied = 1;
		r_tmp = r_tmp->next;
	}
	input->start->occupied = 1;
}

static void		room_dist2(t_rooms *r_tmp, t_hashlst *h_tmp,
		int tmpdst, t_lemin *input)
{
	t_links		*l_tmp;

	l_tmp = r_tmp->linx;
	while (l_tmp)
	{
		h_tmp = hash_lookup(l_tmp->link, input->hasht);
		if (((t_rooms *)h_tmp->data)->dist == -1 ||
				(((t_rooms *)h_tmp->data)->dist > tmpdst))
		{
			input->state++;
			((t_rooms *)h_tmp->data)->dist = tmpdst + 1;
		}
		l_tmp = l_tmp->next;
	}
}

int				room_dist(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_hashlst	*h_tmp;
	int			tmpdst;

	tmpdst = 0;
	while (input->state)
	{
		r_tmp = input->roomhead;
		input->state = 0;
		while (r_tmp)
		{
			if (r_tmp != input->start && r_tmp->dist == tmpdst)
			{
				room_dist2(r_tmp, h_tmp, tmpdst, input);
			}
			r_tmp = r_tmp->next;
		}
		tmpdst++;
	}
	if (input->start->dist == -1)
		error_exit(2);
	blockpath(input);
	return (1);
}
