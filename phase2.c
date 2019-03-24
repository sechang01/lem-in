/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phase2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:34:01 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 01:15:40 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
t_links			*ft_lstreverse(t_links *l_tmp)
{
	t_links		*head;
	t_links		*curr;
	t_links		*prev;
	t_links		*next;

	head = l_tmp;
	curr = l_tmp;
	prev = NULL;
	next = l_tmp;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
	return (head);

}
*/


void			blockpath(t_lemin *input)
{
	t_rooms		*r_tmp;

	r_tmp = input->roomhead;
	while (r_tmp)
	{
		if (r_tmp->dist == 999999999 || r_tmp->pathnbr > input->paths_taken || !r_tmp->pathnbr)
			r_tmp->occupied = 1;
		r_tmp = r_tmp->next;
	}
	input->start->occupied = 1;
}

static void		room_dist_reset(t_lemin *input)
{
	t_rooms		*r_tmp;

	r_tmp = input->roomhead;
	while (r_tmp)
	{
		if (r_tmp != input->end && r_tmp != input->start && !r_tmp->pathnbr)
			r_tmp->dist = 999999999;
		r_tmp = r_tmp->next;
	}
}

static void		room_retrace(t_rooms *r_tmp, int tmpdst, t_lemin *input)
{
	t_links		*tmp;
	t_rooms		*tmp2;
	int			p;



	r_tmp->pathnbr = input->pathnbr;
	r_tmp->bfs = 1;
	tmp = r_tmp->linx;
	while (tmp)
	{
		tmp2 = ((t_rooms *)hash_lookup(tmp->link, input->hasht)->data);
		if (tmp2->dist == tmpdst - 1)
		{
			if (tmp2 != input->end)
				tmp2->bfs = 1;
			tmp2->pathnbr = input->pathnbr;
			if (tmp2 == input->end)
			{
				ft_printf("complete\n");
				ft_printf("Turns: %d\n", input->pathnbr);
				ft_printf("Path Dist: %d\n", input->path_dist);
				p = input->ants_in / input->pathnbr + input->path_dist;
				if (input->best_dist > p)
				{
					input->best_dist = p;
					input->paths_taken = input->pathnbr;
				}
				room_dist_reset(input);
				room_dist(input);
				break ;
			}
			else
			{
				room_retrace(tmp2, tmpdst - 1, input);
				break ;
			}
		}
		tmp = tmp->next;
	}
}


static void		room_dist2(t_rooms *r_tmp, int tmpdst, t_lemin *input)
{
	t_links		*l_tmp;
	t_rooms		*h_tmp;

	//	ft_printf("%s \n", r_tmp->linx->link);
	//	r_tmp->linx = ft_lstreverse(r_tmp->linx);

	//	ft_printf("%s \n", r_tmp->linx->link);
	//	exit(1);
	l_tmp = r_tmp->linx;
	while (l_tmp)
	{
		h_tmp = ((t_rooms*)hash_lookup(l_tmp->link, input->hasht)->data);
		if ((h_tmp->dist == 999999999 || h_tmp->dist > tmpdst) && !h_tmp->bfs)
		{
			if (h_tmp == input->start)
			{
				//				getchar();
				h_tmp->dist--;
				input->pathnbr++;
//				r_tmp->pathnbr = input->pathnbr;
				input->path_dist = r_tmp->dist;
				room_retrace(r_tmp, tmpdst, input);
			}
			input->state++;
	//		r_tmp->female++;
			h_tmp->dist = tmpdst + 1;
		}
	//	if (h_tmp->dist <= tmpdst)
	//		r_tmp->male++;
		l_tmp = l_tmp->next;
	}
}

int				room_dist(t_lemin *input)
{
	t_rooms		*r_tmp;
	int			tmpdst;

	tmpdst = 0;

	while (input->state)
	{
		r_tmp = input->roomhead;
		input->state = 0;
		while (r_tmp)
		{
			//	ft_printf("renter\n");
			if (r_tmp != input->start && r_tmp->dist == tmpdst && !r_tmp->bfs)
			{
				//	ft_printf("enter\n");
				room_dist2(r_tmp, tmpdst, input);
			}
			r_tmp = r_tmp->next;
		}
		tmpdst++;
	}
	if (input->start->dist == 999999999)
		error_exit(2);
	blockpath(input);

	ft_printf("Best: %d Numpaths: %d\n", input->best_dist, input->paths_taken);
	return (1);
}



int			testf(t_lemin *input)
{
//	print_usage(input, input->roomhead);
//	exit(1);
	return (1);
}
/*
   void		node_neighbors_nbr(t_lemin *input)
   {
   t_links		*tmp;
   t_rooms		*tmp2;

   tmp = input->end->linx;
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


   void		makeshift_bfs(t_lemin *input)
   {
   t_links		*tmp;
   t_rooms		*tmp2;

   tmp = input->end->linx;

   while (tmp)
   {
   tmp2 = ((t_rooms *)hash_lookup(tmp->link, input->hasht)->data);
   if (tmp2->dist 
   tmp = tmp->next;
   }
   }
   */


/*
   void			blockpath(t_lemin *input)
   {
   t_rooms		*r_tmp;

   r_tmp = input->roomhead;
   while (r_tmp)
   {
   if (r_tmp->dist == 999999999)
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
   if (((t_rooms *)h_tmp->data)->dist == 999999999 ||
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
   room_dist2(r_tmp, h_tmp, tmpdst, input);
   r_tmp = r_tmp->next;
   }
   tmpdst++;
   }
   if (input->start->dist == 999999999)
   error_exit(2);
   blockpath(input);
   return (1);
   }*/
