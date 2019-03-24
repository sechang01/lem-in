/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:31:04 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 04:55:19 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	usage_flags(t_lemin *input, t_rooms *r)
{
	if (input->usage == 'b')
	{
		ft_printf("Number of Ants: %d\n", input->ants_in);
		ft_printf("Number of Rooms: %d\n", input->nbrofrooms);
		ft_printf("Starting Room: %s\n", input->start->name);
		ft_printf("Ending Room: %s\n", input->end->name);
	}
	else if (input->usage == 'n' || input->usage == 'd')
		print_usage(input, r);
	exit(1);
}

void	print_usage(t_lemin *input, t_rooms *r)
{
	t_rooms *tmp;
	t_links	*tmp2;

	tmp = r;
	while (tmp)
	{
		if (input->usage == 'n')
		{
			if (tmp == input->start)
				ft_printf(" - S:");
			else if (tmp == input->end)
				ft_printf(" - E:");
			ft_printf("Room name: %s Neighbors:", tmp->name);
			ft_printf("%s:%d:%d:%d       , ", tmp->name, ((t_rooms *)
				hash_lookup(tmp->name, input->hasht)->data)->dist, ((t_rooms *)hash_lookup(tmp->name, input->hasht)->data)->pathnbr,((t_rooms *)hash_lookup(tmp->name, input->hasht)->data)->occupied);
			tmp2 = tmp->linx;
			while (tmp2)
			{
				ft_printf("%s:%d:%d:%d, \n", tmp2->link, ((t_rooms *)
				hash_lookup(tmp2->link, input->hasht)->data)->dist, ((t_rooms *)hash_lookup(tmp2->link, input->hasht)->data)->pathnbr,				((t_rooms *)hash_lookup(tmp2->link, input->hasht)->data)->occupied);
				tmp2 = tmp2->next;
			}
			ft_printf("\n");
		}
		else if (input->usage == 'd')
		{
			ft_printf("Room name: %s, Distance: %d, Occupied: %d\n",
					tmp->name, tmp->dist, tmp->occupied);
		}
		tmp = tmp->next;
	}
	ft_printf("Nbr of Ants: %d\n", input->ants_in);
	ft_printf("Nbr paths taken: %d\n", input->paths_taken);
	ft_printf("Nbr of Turns: %d\n", input->best_turn);
}
