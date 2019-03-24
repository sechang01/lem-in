/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase3b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:01:56 by sechang           #+#    #+#             */
/*   Updated: 2019/03/23 21:13:45 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
int			room_crossed_dupecheck(t_lemin *input, t_rooms *curr, t_rooms *new)
{
	t_links		*tmp;

	tmp = new->crossed;
	while (tmp)
	{
		if (!ft_strcmp(tmp->link, curr->name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		room_crossed_names(t_lemin *input, t_rooms *curr, t_rooms *new)
{
	t_links		*tmp;
	t_links		*x;

	tmp = new->crossed;
	// links for NEW of CURR (that becomes prevroom) 
	//
	//
	if (!(room_crossed_dupecheck(input, curr, new)))

		if (!(linkcheck(tmp, curr->name)))
		{
			if (!(x = (t_links *)malloc(sizeof(t_links))))
				error_exit(1);
			x->link = ft_strdup(curr->name);
			//	ft_printf("New Link found: %s\n", x->link);
			if (new->crossed)
				x->next = new->crossed;
			else
				x->next = 0;
			new->crossed = x;
		}
}
*/
void		linkem(t_lemin *input, t_rooms *old, t_rooms *curr, t_rooms *new)
{
	t_rooms		*curr_tmp;
	int			*to;
	int			*tb;

	//	ft_printf("Curr: %s vs New: %s\n", curr->name, new->name);
	curr_tmp = curr;
	curr_tmp->occupied = 0;
	//	new->begin_path = curr_tmp->begin_path;
	//	curr_tmp->begin_path = NULL;         necessary???
	new->occupied = 1;
//	if (new != curr)
//		new->counter++;
	if (input->thkey == 1)
		input->anthead = new;
	else if (input->thkey == 2)
		input->anttail = new;
	if (input->prevroom && input->prevroom != new)
		input->prevroom->next = new;
	//	room_crossed_names(input, curr, new);
	//	else stuck
//	new->p_me = curr;
	//	ft_printf("new: %s, pme: %s\n", new->name, new->p_me->name);
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
	ft_printf("L%d-%s End", input->antnum, input->end->name);
}

/*
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

   ft_printf("Number of Ants: %d\n", input->ants_in);
   ft_printf("Number of Paths: %d\n", numpaths);
   ft_printf("Shortest Path: %d\n", shortest);
//	exit(1);

l_tmp = curr->linx;
while (l_tmp)
{
h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
if (h_tmp->dist > shortest * 1.3 && (!(input->startpathkey = 0)))
h_tmp->occupied = 1;
l_tmp = l_tmp->next;
}
} */

t_rooms		*closest_node2(t_lemin *input, t_rooms *curr)  // maybe key for first and second run through
{
	//	int			disttmp;
	t_links		*l_tmp;
	t_rooms		*h_tmp;
	int			i;

	i = 0;
	//	disttmp = 2147483647;
	// must reset p_me at the start of every turn.
	// two run-throughs. first is setting p_me for collision. second is moving.
	l_tmp = curr->linx;	//<--


	input->closest = (curr == input->start) ? NULL : curr;
	while (l_tmp)			// input->p_me , occupied = 0
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);

		//		if (h_tmp == input->start)
		//		{
		//			l_tmp = l_tmp->next;
		//			continue ;
		//		}
		if (h_tmp == input->end)
		{
		//	exit(1);
			close_end(input, curr);
			input->antnum++;
			input->closest = NULL;
			break ;
		}

		/*		if (h_tmp != input->start && h_tmp->occupied && !i && !h_tmp->collision && input->closest)
				{
		//			compare distances!

		if (h_tmp->p_me->dist - curr->dist != 0)
		{
		h_tmp->collision = h_tmp->p_me;
		h_tmp->collision->dist_diff = h_tmp->p_me->dist - curr->dist;
		}
		//	ft_printf("\n%s is Looking but occupied by: %s\n", curr->name, h_tmp->name);

		//		ft_printf("Ant from Node: %s Took your spot!\n", h_tmp->collision->name);
		//sleep(1);
		}*/

		if (curr == input->start)
		{
			if (!h_tmp->occupied)
			{
				ft_printf("S%dS: ", h_tmp->pathnbr);
				//	exit(1);
				//		h_tmp->p_me = curr;
				//			disttmp = h_tmp->dist;
				input->closest = h_tmp;
				break ;
			}

			//			ft_printf("start ");	
		}
		else if (!h_tmp->occupied && curr->pathnbr == h_tmp->pathnbr && h_tmp->dist < curr->dist)
		{
			ft_printf(" %d : ", h_tmp->pathnbr);
			//	exit(1);
			//		h_tmp->p_me = curr;
			//			disttmp = h_tmp->dist;
			input->closest = h_tmp;
			break ;
		}
		i++;
		l_tmp = l_tmp->next;
	}
	return (input->closest);
}
/*
t_rooms		*closest_node3(t_lemin *input, t_rooms *curr)  // maybe key for first and second run through
{
	int			disttmp;
	t_links		*l_tmp;
	t_rooms		*h_tmp;

	disttmp = 2147483647;
	l_tmp = curr->linx;


	input->closest = (curr == input->start) ? NULL : curr;

	while (l_tmp)			// input->p_me , occupied = 0
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp == input->end)
		{
			close_end(input, curr);
			input->antnum++;
			input->closest = NULL;
			break ;
		}
		if (!h_tmp->occupied && h_tmp->dist <= disttmp)
		{
			disttmp = h_tmp->dist;
			input->closest = h_tmp;
		}
		l_tmp = l_tmp->next;
	}
	return (input->closest);
}






int			compare_next_path(t_lemin *input, t_rooms *r)
{
	t_links		*l_tmp;
	t_rooms		*h_tmp;

	l_tmp = r->linx;
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (!h_tmp->occupied && !h_tmp->intent)
		{
			return (h_tmp->dist);
		}
		l_tmp = l_tmp->next;
	}
	return (0);
}

void		collision_decide(t_lemin *input, t_rooms *curr, t_rooms *vs)
{
	int		curr_d;
	int		vs_d;

	curr_d = compare_next_path(input, curr);
	vs_d = compare_next_path(input, vs);





}

void		pme_init_lst(t_lemin *input, t_rooms *r)
{
	if (!input->pme_lst)
		input->pme_lst = r;


}

void		set_ant_p_me(t_lemin *input, t_rooms *curr)
{
	t_links		*l_tmp;
	t_rooms		*h_tmp;

	l_tmp = curr->linx;
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp->occupied)
		{
			l_tmp = l_tmp->next;
			continue ;
		}
		if (h_tmp == input->end)
			break ;
		if (h_tmp->p_me) //path collision found!
		{
			collision_decide(input, curr, h_tmp->p_me);
			break ;
		}
		else
		{
			h_tmp->p_me = curr;
			pme_init_lst(input, h_tmp);
			curr->intent = h_tmp;
			break ;
		}
		l_tmp = l_tmp->next;
	}
}
*/
t_rooms		*closest_node(t_lemin *input, t_rooms *curr, int hstate, int tstate)
{
	//	if (curr == input->start && input->startpathkey)
	//		start_path_check(input, curr);
	hstate = (input->anthead == curr) ? 1 : 0;
	tstate = (input->anttail == curr) ? 1 : 0;

	input->blockstate = 1;
	input->closest = closest_node2(input, curr);	//closest already sorted in order


	if (input->closest == curr)
		input->blockstate = 33;			//what's this?	when ant's best move is not moving

	//	ft_printf("closest node dist: %d \n", input->closest->dist);
	//	exit(1);
	if (input->closest != curr && input->closest != NULL)
	{
		input->closest->next = curr->next;
		if (hstate == 1 && (input->thkey = 1))
			linkem(input, input->closest->next, curr, input->closest);
		else if (tstate == 1 && (input->thkey = 2))
			linkem(input, input->closest->next, curr, input->closest);
		else
			linkem(input, input->closest->next, curr, input->closest);
		if ((!(input->thkey = 0)))
			ft_printf("L%d-%s ", input->antnum, input->closest->name);
		input->antnum++;
	}


	input->start->occupied = 1;
	input->end->occupied = 0;
	return (input->closest);
}





// Merge sort links by distance? So you instantly know which is the closest - necessary? links are pretty short
// Lookup via hashtable
/* Collision Node Search
 * p_me // Node about to move here bc shortest distance
 * if p_me = p_me, collision found
 * function to add distances of 1st and second choices of both nodes to see which is lower
 * Save Dist Gained
 * If fixing this collision results in a new collision
 * Compare Dist Gained vs new collision's Dist Gained. If Dist Gained is negative, restart?
 * 
 *
 *
 *
 *
 * Starting node - How to choose which nodes to send to? 
 * Currently we use a multiplier of (shortest path) to avoid long long paths
 * If 1 path, = path_dist + ants_in = answer
 * If 2 path, = (ants_re/2 + path_dist1) + (ants_re/2 + path_dist2) = answer
 * If n paths, = ants_re/n + path_dist1 ... to n = answer
 * Disregard Path if: ants_re path_distx > 
 *
 * If collision... && dist of collision < shortest_path
 *
 * */
