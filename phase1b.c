/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase1b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:43:10 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 01:14:40 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				linkcheck(t_links *linx, char *dupecheck)
{
	t_links				*tmp;

	tmp = linx;
	while (tmp)
	{
		if (!ft_strcmp(dupecheck, tmp->link))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void		links2(t_lemin *input)
{
	t_links				*newlinka;
	t_links				*newlinkb;
	t_hashlst			*room_one;
	t_hashlst			*room_two;

	if (!(room_one = hash_lookup(input->ro[0], input->hasht)) ||
			(!(room_two = hash_lookup(input->ro[1], input->hasht))))
		error_exit(1);
	if (!(linkcheck(((t_rooms *)room_one->data)->linx,
					((t_rooms *)room_two->data)->name)))
	{
		if (!(newlinka = malloc(sizeof(t_links))) ||
				(!(newlinkb = malloc(sizeof(t_links)))))
			error_exit(1);
		newlinka->link = ((t_rooms *)room_two->data)->name;
		newlinka->next = ((t_rooms *)room_one->data)->linx;
		((t_rooms *)(room_one->data))->linx = newlinka;
		newlinkb->link = ((t_rooms *)(room_one->data))->name;
		newlinkb->next = ((t_rooms *)(room_two->data))->linx;
		((t_rooms *)(room_two->data))->linx = newlinkb;
		ft_printf("%s-%s\n", newlinkb->link, newlinka->link);
	}
	else
		error_exit(1);
}

int				links(t_lemin *input, int k, char *line)
{
	if (line && line[0] == '#')
		return (0);
	if (input->ro)
		ft_strsplitdel(&input->ro);
	if ((input->ro = (lm_strsplit(line, '-', 2))))
	{
		links2(input);
	}
	else
		error_exit(1);
	return (0);
}
