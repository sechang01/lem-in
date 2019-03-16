/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:33:31 by sechang           #+#    #+#             */
/*   Updated: 2019/03/14 15:57:10 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			test_start(t_lemin *input)
{
	t_links		*l_tmp;
	int			i;

	ft_printf("----------------- TEST START ---------------\n");
	ft_printf("START: %s\n", input->start->name);
	ft_printf("END: %s\n", input->end->name);
	i = 0;
	l_tmp = input->start->linx;
	ft_printf("\t\t\t\t\t");
	while (l_tmp)
	{
		i++;
		ft_printf("%d. %s\n", i, l_tmp->link);
		l_tmp = l_tmp->next;
	}
	ft_printf("\n");
}

void			test_output3(t_lemin *input)
{
	int			i;
	t_hashlst	*m;

	i = 0;
	ft_printf("COMMENCING TEST OUTPUT 3\n");
	while (i < HASHSIZE)
	{
		if ((m = input->hasht->hashtab[i]))
		{
			while (m)
			{
				if (((t_rooms *)m->data)->occupied)
					ft_printf("name: %s, dst: %d, occupied: %d\n", m->key,
					((t_rooms *)m->data)->dist, ((t_rooms *)m->data)->occupied);
				m = m->next;
			}
		}
		i++;
	}
}

void			test_output2(t_lemin *input, t_rooms *head, char *name)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;
	int			i;

	ft_printf("TEST OUTPUT COMMENCE2: %s \n", name);
	r_tmp = input->anthead;
	if ((!(i = 0)) && input->anthead && input->anttail)
		ft_printf("H: %s\nT: %s\n", input->anthead->name, input->anttail->name);
	while (r_tmp)
	{
		ft_printf("%s - dst: %d  Neighbors:\n", r_tmp->name, r_tmp->dist);
		if (i++ > input->ants_in)
			ft_printf("///////////////////////////////////////erroring out\n");
		ft_printf("%s(%d)->", r_tmp->name, r_tmp->dist);
		if (r_tmp->occupied == 0)
			ft_printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		l_tmp = r_tmp->linx;
		while (l_tmp)
		{
			ft_printf("\t%s\n", l_tmp->link);
			l_tmp = l_tmp->next;
		}
		r_tmp = r_tmp->next;
	}
	ft_printf("Num of Links:%d\n", i);
}

void			test_output(t_lemin *input, t_rooms *head)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;

	ft_printf("TEST OUTPUT COMMENCE: \n");
	ft_printf("Ants In: %d\n\n", input->ants_in);
	r_tmp = head;
	while (r_tmp)
	{
		ft_printf("%s - dst: %d, occupied: %d,  Neighbors:\n",
				r_tmp->name, r_tmp->dist, r_tmp->occupied);
		l_tmp = r_tmp->linx;
		while (l_tmp)
		{
			ft_printf("\t%s\n", l_tmp->link);
			l_tmp = l_tmp->next;
		}
		r_tmp = r_tmp->next;
	}
}

static void		print_neighbors(t_lemin *input, t_rooms *n)
{
	int			i;
	t_links		*p;

	p = n->linx;
	i = 1;
	ft_printf("\tRoom (dst: %d) %s's Neighbors:\n", n->dist, n->name);
	while (p)
	{
		ft_printf("%d. Neighbors: %s\n", i, p->link);
		i++;
		p = p->next;
	}
}
