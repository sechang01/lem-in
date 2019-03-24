/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:43:00 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 05:46:22 by sechang          ###   ########.fr       */
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
	//	r_tmp->occupied = 0;
//		r_tmp->p_me = NULL;
		rr_tmp = r_tmp;
		r_tmp = r_tmp->next;
		rr_tmp->next = NULL;
	}
	//	if (input->anthead)
	//		input->anthead = NULL;
	//	if (input->anttail)
	//		input->anttail = NULL;
	//	if (input->prevroom)
	//		input->prevroom = NULL;
}

void		cleardata(t_lemin *input, t_rooms *beginlst)
{
	t_rooms		*r_tmp;
	//	t_rooms		*rr_tmp;

	r_tmp = beginlst;
	while (r_tmp)
	{
		//		rr_tmp = r_tmp;
	//	r_tmp->p_me = 0;
		r_tmp = r_tmp->next;
		//		rr_tmp->next = NULL;
	}
}

void		start_nexus(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;
	int			i;

	i = 1;
	//	input->blocked = 13; //paths_taken vs bneck?
	l_tmp = input->start->linx;
//	while (l_tmp && input->ants_searching < input->ants_in && i <= (input->bneck - input->blocked))

	while (l_tmp && input->ants_searching < input->ants_in && (i <= input->pathnbr))
	{
//	ft_printf("i: %d, i->startnbr: %d\n", i, input->startnbr, input->blocked);
		input->startnbr = i;
		if ((r_tmp = closest_node(input, input->start, -1, -1)))
		{
	//		r_tmp->begin_path = r_tmp;
			input->ants_searching++;
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
//		else
//			break ;
		i++;
		//		ft_printf("Dist: %d\n", r_tmp->dist);

		l_tmp = l_tmp->next;
	}
}

static void	initc(t_lemin *input)
{
	input->turn = 1;
	input->anthead = NULL;
	input->anttail = NULL;
	//	input->entrances = 0;
	input->prevroom = NULL;

	input->ants_searching = 0;
	input->blockstate = 0;
//	input->ants_in = input->in_cpy;
//	input->ants_out = input->out_cpy;
	//	input->startpathkey = 1;
}

static int	gogo_ants2(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_rooms		*rr_tmp;
	t_rooms		*close_tmp;

	ft_printf("\n");
	input->antnum = 1 + input->ants_out;
	r_tmp = input->anthead;
	input->prevroom = NULL;
	while (r_tmp)
	{
//		ft_printf("test   %s	%d *** %d \n", r_tmp->name, input->tries, input->turn);
		if ((close_tmp = closest_node(input, r_tmp, -1, -1)))
			input->prevroom = close_tmp;
		rr_tmp = r_tmp;
		r_tmp = r_tmp->next;
		if (input->blockstate != 33)
		{
			rr_tmp->next = NULL;
		}
		else
		{
			//			input->paths_taken--;
			ft_printf("\n\n\nCN: %s - path: %d - dist: %d \n", close_tmp->name,	close_tmp->pathnbr, close_tmp->dist);
	//		((t_rooms *)hash_lookup(close_tmp->name, input->hasht)->data)->stuck++;
		}
	}
	if (input->anttail)
		input->anttail->next = NULL;
	start_nexus(input);
	//	exit(1);
	if (input->ants_out >= input->ants_in)
		return (1);
	input->turn++;
	return (0);
}
/*
void		start_paths_used(t_lemin *input)
{
	t_links		*s;
	int			turns_est;
	int			turns_tmp;

	turns_tmp = 0;
	turns_est = 2147483647;
	input->paths_taken = 1;
	s = input->start->linx;
	while (s)
	{
		if ((turns_tmp = input->ants_in / input->paths_taken + ((t_rooms *)hash_lookup(s->link, input->hasht)->data)->dist) < turns_est)		//ants re //dst
			turns_est = turns_tmp;
		else
			break ;
		if ((input->paths_taken++) >= input->bneck)
			break ;
		s = s->next;
	}
	ft_printf("Nbr Paths: %d\n", input->paths_taken);
	//	exit(1);
}
*/
/*
void		validpaths(t_lemin *input)
{
	t_links		*tmp;
	int			start_paths;
	int			end_paths;

	start_paths = 0;
	end_paths = 0;
	tmp = input->start->linx;
	while (tmp)
	{
		if (((t_rooms *)hash_lookup(tmp->link, input->hasht)->data)->dist <= input->best_turn)
			input->bneck++;
		tmp = tmp->next;
	}
	// if inputbest turn exists! (only generator files)
	// should test all paths first ?
	//	input->bneck = end_paths >= start_paths ? start_paths : end_paths;

	ft_printf("Start Paths: %d, End Paths: %d, Bneck: %d\n", start_paths, end_paths, input->bneck);
	//	exit(1);
}

*/
/*
void		connecting_validpaths(t_lemin *input)
{
	t_links		*tmp;
	int			start_paths;
	int			end_paths;

	start_paths = 0;
	end_paths = 0;
	tmp = input->start->linx;
	
//	   while (tmp)
//	   {
//	   if (((t_rooms *)hash_lookup(tmp->link, input->hasht)->data)->dist <= input->best_turn)
//	   input->bneck++;
//	   tmp = tmp->next;
//	   }
	   
	// if inputbest turn exists! (only generator files)
	// should test all paths first ?
	while (tmp)
	{
		if (((t_rooms *)hash_lookup(tmp->link, input->hasht)->data)->dist <= input->best_turn)
			start_paths++;
		tmp = tmp->next;
	}
	tmp = input->end->linx;
	while (tmp)
	{
		if (((t_rooms *)hash_lookup(tmp->link, input->hasht)->data)->dist <= input->best_turn)
			end_paths++;
		tmp = tmp->next;
	}
	input->bneck = end_paths >= start_paths ? start_paths : end_paths;

	ft_printf("Start Paths: %d, End Paths: %d, Bneck: %d\n", start_paths, end_paths, input->bneck);
	//	exit(1);
}
*/
/*
void		start_test(t_lemin *input, t_rooms *head)
{
	t_links *tmp;
	int		i;

	i = 0;
	tmp = head->linx;
	while (tmp)
	{
		i++;
		ft_printf("%d. Sorted Dist: %d\n", i, ((t_rooms *)hash_lookup(tmp->link, input->hasht)->data)->dist);

		tmp = tmp->next;
	}
	exit(1);
}
*/
/*
void		dress_rehearsal(t_lemin *input)
{
	t_rooms *ant;
	t_rooms *tmp;
	t_links *tmp2;
	int		state;
	int		i = 1;
	t_rooms	*spath;
	int		workingpaths;

	workingpaths = 0;
	while (i <= input->paths_taken)
	{
		ft_printf(" ~%d\n", i);
		ant = input->end;
		while (ant != input->start)
		{
			tmp2 = ant->linx;
			while (tmp2)
			{
				if (ant == input->end)
					spath = tmp;
				state = 0;
				tmp = ((t_rooms *)hash_lookup(tmp2->link, input->hasht)->data);

				//		ft_printf("Antdist: %d, TmpDst: %d\n", ant->dist, tmp->dist);
				//			ft_printf("TmpPath: %s, TmpDist: %d\n", tmp->name, tmp->dist);
				if ((!tmp->occupied && tmp->dist == ant->dist + 1) || tmp == input->start)
				{
					state = 1;
					ant = tmp;
					ant->occupied = 1;
					ft_printf("Path: %s, Dist: %d\n", ant->name, ant->dist);
					if (tmp == input->start)
						workingpaths++;
					break ;
				}
				tmp2 = tmp2->next;
			}

			ft_printf("-----------\n");
			if (!state)
			{
				ft_printf("Stuck @ %s \n", spath->name);
				spath->occupied = 1;
				//				ft_printf("Path: %s, Dist: %d\n", ant->name, ant->dist);
				//				ft_printf("End: %s End dist: %d\n", input->end->name, input->end->dist);
				break ;
				//	exit(1);
			}
		}
		if (spath && state)
			ft_printf("Finished @ %s \n", spath->name);
		ft_printf("-----------\n");
		i++;
	}
	ft_printf("working paths: %d\n", workingpaths);
	exit(1);
}*/

int			gogo_ants_start(t_lemin *input)
{
//	sort_neighbors_dist(input);

	//	start_test(input, input->start);

	//connecting_validpaths(input);

//	validpaths(input);
//	start_paths_used(input);
	if (input->usage && input->usage != 't')
		usage_flags(input, input->roomhead);
	clearlinks(input, input->roomhead);

	//	dress_rehearsal(input);
//	input->in_cpy = input->ants_in;
//	input->out_cpy = input->ants_out;

//	input->tries = 0;
	gogo_ants(input);
	return (0);
}
/*
void		print_collision(t_lemin *input, t_rooms *r)
{
	t_rooms	*tmp;
	int		i;

	i = 1;
	tmp = r;
	//	ft_printf("Anthead: %s\n", r->name);
	while (tmp)
	{
		if (tmp->collision)
			ft_printf("%d. Node: %s  Collisions: %s -- %d\n", i++, tmp->name,  tmp->collision->name, tmp->collision->dist_diff);
		tmp = tmp->next;
	}
	ft_printf("-----------------\n");
	//	exit(1);
}
*/
/*
void		start_neighbor_counter(t_lemin *input)
{
	t_links		*tmp;
	int			i;
	int			sum;
	t_rooms		*tmp2;

	i = 1;
	sum = 0;
	tmp = input->start->linx;
	while (tmp)
	{
		tmp2 = ((t_rooms *)hash_lookup(tmp->link, input->hasht)->data);
		ft_printf("%i  %s - counter: %d - dist: %d - stuck:%d\n", i, tmp->link,
				tmp2->counter, tmp2->dist, tmp2->stuck);
		i++;
		if (tmp2->dist >= 25)
			tmp2->occupied = 1;
		sum += tmp2->counter;
		tmp = tmp->next;
	}

	ft_printf("sum: %i\n", sum);
	ft_printf("ants: %i\n", input->in_cpy);
	ft_printf("antsout: %i\n", input->ants_out);
	ft_printf("best turn: %i\n", input->best_turn);
}
*/
/*
void		start_neighbor_block(t_lemin *input)
{
	t_links		*tmp;
	t_rooms		*tmp2;

	tmp = input->start->linx;
	while (tmp)
	{
		tmp2 = ((t_rooms *)hash_lookup(tmp->link, input->hasht)->data);
		if (tmp2->dist >= 25)
		{
			tmp2->occupied = 1;
		}
		tmp = tmp->next;
	}
}
*/
/*
void		print_hasht(t_lemin *input)
{
	t_hasharr	*tmp;
	t_hashlst	*tmp2;
	t_links		*tmp3;
	int			i;
	int			counter = 0;

	i = 0;
	tmp = input->hasht;
	while (i < HASHSIZE)
	{

		tmp2 = tmp->hashtab[i];
		while (tmp2)
		{
			tmp3 = ((t_rooms *)tmp2->data)->crossed;
			if (((t_rooms *)tmp2->data)->counter)
			{
				ft_printf("Name: %s, Male: %d, Female: %d, Stuck %d, Dist %d, Counter: %d\n",
						((t_rooms *)tmp2->data)->name,
						((t_rooms *)tmp2->data)->male,
						((t_rooms *)tmp2->data)->female,
						((t_rooms *)tmp2->data)->stuck,
						((t_rooms *)tmp2->data)->dist,
						((t_rooms *)tmp2->data)->counter);

				ft_printf("Crossed:\t\t\t");
				counter = 0;
				while (tmp3)
				{
					ft_printf("%s, ", tmp3->link);
					counter++;
					tmp3 = tmp3->next;
				}
				ft_printf(" -  %d\n", counter);

			}
			//--------------
						if (((t_rooms *)tmp2->data)->stuck)
						{
			//				ft_printf("%s: ", ((t_rooms *)tmp2->hashtab[i]->data)->name);
			//				ft_printf("stuck: %d, ", ((t_rooms *)tmp2->hashtab[i]->data)->stuck);

			if (((t_rooms *)tmp2->data)->stuck >= (input->best_turn / 2))
			{
			if (((t_rooms *)tmp2->data)->begin_path->occupied == 0)
			input->blocked++;
			((t_rooms *)tmp2->data)->begin_path->occupied = 1;
			ft_printf("Blocking: %s\n",((t_rooms *)tmp2->data)->begin_path->name);
			}
			//
			//				ft_printf("Name: %s, Male: %d, Female: %d, Stuck %d, Dist %d\n",
			ft_printf("Name: %s, Male: %d, Female: %d, Stuck %d, Dist %d, Block: %s, Counter: %d\n",
			((t_rooms *)tmp2->data)->name,
			((t_rooms *)tmp2->data)->male,
			((t_rooms *)tmp2->data)->female,
			((t_rooms *)tmp2->data)->stuck,
			((t_rooms *)tmp2->data)->dist,
			((t_rooms *)tmp2->data)->begin_path->name,
			((t_rooms *)tmp2->data)->counter);
			//		((t_rooms *)hash_lookup((((t_rooms *)tmp2->hashtab[i]->data)->linx->link), h)->data)->female);
			//					((t_rooms *)tmp->hashtab[i]->data)->collision->name);
			//
			//		exit(1);
			}
			//--------------	
			tmp2 = tmp2->next;
		}
		i++;
	}
	ft_printf("Blocked %d Rooms\n", input->blocked);

}
*/


int			gogo_ants(t_lemin *input)
{
	initc(input);
	//	ft_printf("out: %d, in: %d, turn: %d, best: %d, paths: %d\n", input->ants_out, input->ants_in, input->turn, input->best_turn, input->paths_taken);
	while (input->ants_out < input->ants_in)
	{
		if (gogo_ants2(input))
			break ;
		/*		if (input->best_turn && input->turn > input->best_turn && !input->tries)
				{
		//	exit(1);
		//			print_collision(input, input->anthead);
		//			exit(1);
		ft_printf("\n\n\n");
		sleep(3);
		input->tries++;
		clearlinks(input, input->anthead);
		print_hasht(input);
		start_neighbor_counter(input);
		exit(1);
		gogo_ants(input);
		//			break ;				// break or start over? dress_hearsal to perform;
		}*/
	}

	//			print_collision(input, input->anthead);
	//


//	if (!input->tries)
//	{
//		sleep(3);
//		input->tries++;
//		clearlinks(input, input->anthead);

	//	start_neighbor_counter(input);
//		print_hasht(input);
//		gogo_ants(input);
//	}




	if (input->usage == 't')
		ft_printf("\n\n\nTURNS: %d vs BEST: %d\n", input->turn, input->best_turn);
	else
		ft_printf("\n");
	return (0);
}
