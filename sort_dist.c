/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:36:16 by sechang           #+#    #+#             */
/*   Updated: 2019/03/16 20:47:21 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	sort_neighbors_dist(t_lemin *input)
{
	t_rooms		*tmp;
	t_links		*tmp2;

/*	tmp = input->roomhead;
	while (tmp)
	{
			ft_printf("Room name: %s Neighbors:", tmp->name);
			tmp2 = tmp->linx;
			while (tmp2)
			{
				ft_printf("%s:%d, ", tmp2->link, ((t_rooms *)
				hash_lookup(tmp2->link, input->hasht)->data)->dist);
				tmp2 = tmp2->next;
			}
			ft_printf("\n");
		tmp = tmp->next;
	}

*/

	tmp = input->roomhead;
	while (tmp)
	{
		if (tmp->linx)
		{
			tmp->linx = lm_mergesort(&tmp->linx, input);
		}
		tmp = tmp->next;
	}


/*
	ft_printf("-------------------------\n\n\n");

	tmp = input->roomhead;
	while (tmp)
	{
			ft_printf("Room name: %s Neighbors:", tmp->name);
			tmp2 = tmp->linx;
			while (tmp2)
			{
				ft_printf("%s:%d, ", tmp2->link, ((t_rooms *)
				hash_lookup(tmp2->link, input->hasht)->data)->dist);
				tmp2 = tmp2->next;
			}
			ft_printf("\n");
		tmp = tmp->next;
	}
exit(1);*/
}