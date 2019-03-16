/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:31:04 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:42:20 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	usage_flags(t_lemin *input)
{
	if (input->usage == 'b')
	{
		ft_printf("Number of Ants: %d\n", input->ants_in);
		ft_printf("Number of Rooms: %d\n", input->nbrofrooms);
		ft_printf("Starting Room: %s\n", input->start->name);
		ft_printf("Ending Room: %s\n", input->end->name);
	}
	else if (input->usage == 'n' || input->usage == 'd')
		print_usage(input);
	exit(1);
}

void	print_usage(t_lemin *input)
{
	t_rooms *tmp;

	tmp = input->roomhead;
	while (tmp)
	{
		if (input->usage == 'n')
		{
			ft_printf("Room name: %s Neighbors:", tmp->name);
			while (tmp->linx)
			{
				ft_printf("%s, ", tmp->linx->link);
				tmp->linx = tmp->linx->next;
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
}
