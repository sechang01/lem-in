/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:09:44 by sechang           #+#    #+#             */
/*   Updated: 2018/11/25 22:05:17 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashix.h"
#include "lem_in.h"

void		test_start(t_lemin *input)
{
	t_links		*l_tmp;
	int			i;


	printf("----------------- TEST START ---------------\n");

	printf("START: %s\n", input->start->name);
	printf("END: %s\n", input->end->name);
	i = 0;
	l_tmp = input->start->linx;
	printf("\t\t\t\t\t");
	while (l_tmp)
	{
		i++;
		printf("%d. %s\n", i, l_tmp->link);
		l_tmp = l_tmp->next;
	}
	printf("\n");
}

void			test_output3(t_lemin *input)
{
	int			i;
	t_hashlst	*m;

	i = 0;
	printf("COMMENCING TEST OUTPUT 3\n");
	while (i < HASHSIZE)
	{
		if ((m = input->hasht->hashtab[i]))
		{
			while (m)
			{
				if (((t_rooms *)m->data)->occupied)
					printf("name: %s, occupied: %d\n", m->key,
						((t_rooms *)m->data)->occupied);
				m = m->next;
			}
		}
		i++;
	}
}

void		test_output2(t_lemin *input, t_rooms *head)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;

	printf("TEST OUTPUT COMMENCE2: \n");
	r_tmp = head;
	if (input->anthead)
		printf("Head: %s\n", input->anthead->name);
	if (input->anttail)
		printf("Tail: %s\n", input->anttail->name);
	printf("\t\t\t\t\t");
	while (r_tmp)
	{
		//		printf("%s - dst: %d  Neighbors:\n", r_tmp->name, r_tmp->dist);
		printf("%s-> -%d-", r_tmp->name, r_tmp->dist);
		if (r_tmp->occupied == 0)
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		//		l_tmp = r_tmp->linx;
		//		while (l_tmp)
		//		{
		//			printf("\t%s\n", l_tmp->link);
		//			l_tmp = l_tmp->next;
		//		}
		r_tmp = r_tmp->next;
	}
	printf("\n");
}

void			linkem(t_lemin *input, t_rooms *old, t_rooms *curr, t_rooms *new, int key)
{
	if (old)
		printf("oldname: %s\n", old->name);
	if (input->prevroom)
		printf("prevroom: %s\n", input->prevroom->name);
	//	curr->next = NULL;
	//	curr = new;
	//	curr->next = NULL;
	curr->occupied = 0;
	new->occupied = 1;
	if (key == 1)
		input->anthead = new;
	else if (key == 2)
		input->anttail = new;
	else if (key == 3)
	{
		curr->next = NULL;
		input->prevroom->next = old;
		return ;
	}
	//		input->anttail = new;
	else
		curr = new;
	new->next = old;
	if (input->prevroom && input->prevroom != new)
		input->prevroom->next = new;
}

void			close_end(t_lemin *input, t_rooms *curr)
{
	curr->occupied = 0;
	if (curr == input->anthead)
	{
		printf("\t\t\t\t\t\tEXITED!\n");
		input->anthead = curr->next;
		if (input->anthead)
		{
			printf("Enthead: %s\n", input->anthead->name);
	//		test_output2(input, input->anthead);	
		}
	}
	else
	{
		printf("else case\n");
		//linkem(input, closest, currcpy, NULL, 3); //body exits
	}
	input->ants_out++;
//	if (curr != input->start)
	printf("L%d-%s ", input->antnum, input->end->name);
	//	disttmp = -1;
	//	break;
}

t_rooms			*closest_node(t_lemin *input, t_rooms *curr)
{
	//	t_rooms 	*r_tmp;
	t_links		*l_tmp;
	t_rooms		*h_tmp;
	t_rooms		*closest;
	t_rooms		*currcpy;
	int			disttmp;
	int			headstate;
	int			tailstate;

	currcpy = curr;
	printf("\n\n\n\nCLOSEST SEARCH! %s\n", curr->name);
	//	if (input->prevroom)
	//		printf("Prev: %s\n", input->prevroom->name);
	//	if (input->anthead)
	//		printf("Anthead: %s\n", input->anthead->name);	
	//	if (input->anttail)
	//		printf("Anttail: %s\n", input->anttail->name);
//		test_output3(input);
	l_tmp = curr->linx;;
	headstate = (input->anthead == curr) ? 1 : 0;
	tailstate = (input->anttail == curr) ? 1 : 0;
	//	test_output2(input, input->anthead);
	//	printf("Headstate: %d\n", headstate);
	//	printf("Tailstate: %d\n", tailstate);
	//	printf("curr node: %s\toccupied?:%d\n", curr->name, curr->occupied);
	disttmp = 2147483647;
	closest = NULL; // ((t_rooms *)(hash_lookup(l_tmp->link, input->hasht))->data);
	while (l_tmp)
	{
		h_tmp = ((t_rooms *)hash_lookup(l_tmp->link, input->hasht)->data);
		if (h_tmp->occupied == 1)
			printf("curr: %s, neighbor: %s, occupied: %d\n",
				curr->name, h_tmp->name, h_tmp->occupied);
		if (h_tmp == input->end)
		{
			close_end(input, curr);
	//		closest = NULL;
			break;
		}
		if (h_tmp->occupied == 0 && h_tmp->dist <= disttmp)//closest->dist)
		{
			disttmp = h_tmp->dist;
			closest = h_tmp;
	//		printf("curr: %s, neighbor: %s\n",
	//				curr->name, h_tmp->name);
		}
		l_tmp = l_tmp->next;
	}
	if (closest != NULL)
	{
		closest->next = curr->next;
		h_tmp = curr->next;
		if (headstate == 1)
		{
			linkem(input, h_tmp, input->anthead, closest, 1);
		}
		else if (tailstate == 1)
		{
			linkem(input, h_tmp, input->anttail, closest, 2);
		}
		else
		{
			linkem(input, h_tmp, curr, closest, 0);
		}
		printf("CURR: %s to NEW: %s\n", curr->name, closest->name);
	if (input->anthead)
		printf("Head: %s\n", input->anthead->name);
	if (input->anttail)
		printf("Tail: %s\n", input->anttail->name);

		input->antnum++;
//		input->start->occupied = 1;
	}
	input->end->occupied = 0;
	return (closest);
}

void	clearlinks(t_lemin *input, t_rooms *beginlst)
{
	t_rooms		*r_tmp;
	t_rooms		*rr_tmp;

	printf("inside clearlinks\n");
	r_tmp = beginlst;
	while (r_tmp)
	{
		rr_tmp = r_tmp;;
		r_tmp = r_tmp->next;
		rr_tmp->next = NULL;
	}
}

void	start_nexus(t_lemin *input)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;
	static int		i = 0;
	static int		key = 0;

	l_tmp = input->start->linx;
	while (l_tmp)
	{
		if (key == 0)
			input->entrances++;
		if (i >= input->ants_in)
		{
			printf("////////////////////////%d, No mo ants\n", i);
			break;
		}
		if ((r_tmp = closest_node(input, input->start)))
		{
//			test_output3(input);	
			printf("Counter: %d\n", i++);
			if (input->anthead == NULL)
			{
				printf("Head created\n");
				input->anthead = r_tmp;
				input->anthead->next = NULL;
			}
			else if (input->anttail == NULL)
			{
				printf("Tail created\n");
				input->anttail = r_tmp;
			}
			else
			{
				printf("+++++++++++++++++++New Ant created\n");
				input->anttail = r_tmp;
//				r_tmp->next = NULL;
				if (input->anttail)
					printf("SNAnttail: %s\n", input->anttail->name);
			}
			if (input->prevroom)
				input->prevroom->next = r_tmp;
			input->prevroom = r_tmp;
		}
		else
			break;
		printf("~~~~~~~~\n\n\n");
		l_tmp = l_tmp->next;
	}
	key++;
}

int		gogo_ants(t_lemin *input)
{
	t_rooms		*r_tmp;
	int			turns;

	test_start(input);
	printf("Initiating gogo_ants\n");
	//Init
	test_output(input, input->roomhead);
	clearlinks(input, input->roomhead);
	input->turn = 1;
	input->anthead = NULL;
	input->anttail = NULL;
	input->entrances = 0;

	printf("Rooms: %d\n", input->nbrofrooms);
	printf("Shortest Path: %d\n", input->start->dist);
	while (input->ants_out < input->ants_in)
	{
		printf("\tTURN: %d -Ants out: %d Ants in: %d\n",
				input->turn, input->ants_out, input->ants_in);
		input->antnum = 1 + input->ants_out;
		r_tmp = input->anthead;
		input->prevroom = NULL;
		while (r_tmp)
		{
			if (input->prevroom)
				printf("prevroom: %s\n", input->prevroom->name);
			input->prevroom = closest_node(input, r_tmp);
			r_tmp = r_tmp->next;
		}
		start_nexus(input);
		input->anttail->next = NULL;
		printf("\n\n\nTURN %d COMPLETE!\n\n\n", input->turn);
		test_output2(input, input->anthead);
		if (input->ants_out >= input->ants_in)
		{
			printf("Entrances: %d\n", input->entrances);
			printf("Shortest Path: %d\n", input->start->dist);
			printf("\tTURN: %d -Ants out: %d Ants in: %d\n",
					input->turn, input->ants_out, input->ants_in);
			break;
		}
		if (input->turn > input->ants_in + 1000)
		{
			printf("Entrances: %d\n", input->entrances);
			printf("Shortest Path: %d\n", input->start->dist);
			exit(1);
		}
		input->turn++;
	}
	printf("\t\t\tTURN: %d    -	Ants out: %d     Ants in: %d\n", input->turn, input->ants_out, input->ants_in);

	return (0);	// if shortest path blocks another path: blockstate;
	// number of ants that did not move
}























static void		print_neighbors(t_lemin *input, t_rooms *n)
{
	int		i;
	t_links	*p;

	p = n->linx;
	i = 1;
	printf("\tRoom (dst: %d) %s's Neighbors:\n", n->dist, n->name);
	while (p)
	{
		printf("%d. Neighbors: %s\n", i, p->link);
		i++;
		p = p->next;
	}
}

int		room_dist(t_lemin *input)
{
	t_rooms 	*r_tmp;
	t_links		*l_tmp;
	t_hashlst	*h_tmp;
	int			tmpdst;
	int			fin_check;

	printf("ROOM DISTANCE\n");
	tmpdst = 0;
	fin_check = 0;
	printf("start dist:%d\n", input->start->dist);
	while (input->state == 0 || input->start->dist == 2147483647)
	{
		r_tmp = input->roomhead;
		input->state = 1;
		while (r_tmp)
		{
			if (r_tmp->dist == tmpdst)
			{
				print_neighbors(input, r_tmp);
				printf("tmpdst room found: %d\n", tmpdst);
				l_tmp = r_tmp->linx;
				while (l_tmp)
				{
					h_tmp = hash_lookup(l_tmp->link, input->hasht);
					printf("%s: h_tmp->data->dist: %d vs tmpdst: %d \n", ((t_rooms *)h_tmp->data)->name, ((t_rooms *)h_tmp->data)->dist, tmpdst);
					if (((t_rooms *)h_tmp->data)->dist > tmpdst)
					{
						printf("\t\t\t");
						((t_rooms *)h_tmp->data)->dist = tmpdst + 1;
						printf("Room: %s Dist: %d \n", ((t_rooms *)h_tmp->data)->name, ((t_rooms *)h_tmp->data)->dist);
						fin_check++;
					}
					l_tmp = l_tmp->next;
				}
			}
			if (r_tmp->dist == 2147483647)
				input->state = 0;
			r_tmp = r_tmp->next;
		}
		tmpdst++;
		//	if (fin_check > input->nbrofrooms * 1.5)
		//		break;
	}
	//	exit(1);
	test_output(input, input->roomhead);
	printf("start dist:%d\n", input->start->dist);
	//	printf("fin_check: %d\n", fin_check);
	printf("inputrooms: %d\n", input->nbrofrooms);
	//	printf("roomhead %p\n", input->roomhead);
	//	printf("r_tmp %p\n", r_tmp);
	return (1);
}

int		ants_in(t_lemin *input, int k, char *line)
{
	//	printf("\tEntering num_ants! \n");
	if (k <= 0)
		return (-1);
	else if ((input->ants_in = ft_atoi(line)))
	{
		//		printf("num_ants:%d\n", input->num_ants);
		input->g++;
		return (1);
	}
	else
		return (-1);
}

//startend == 1, ##start found
//startend == 2, ##end found
//key == 2, rooms
//key == 3, links
void		split(t_lemin *input, t_rooms *tmp, t_links *lks, char **splitee)
{
	//	printf ("Entering Split\n");
	//	if (roomdupcheck(splitee[0], ft_atoi(splitee[1]), ft_atoi(splitee[2])))
	//	{

	tmp->dist = 2147483647;
	tmp->occupied = 0;
	if (input->startend == 1)
	{
		tmp->occupied = 1;
		input->start = tmp;
	}
	else if (input->startend == 2)
	{
		tmp->dist = 0;
		input->end = tmp;
	}
	tmp->name = ft_strdup(splitee[0]);
	tmp->x = ft_atoi(splitee[1]);
	tmp->y = ft_atoi(splitee[2]);
	tmp->linx = NULL;
	tmp->next = input->roomhead;
	input->roomhead = tmp;
	if (!(hash_install(splitee[0], tmp, input->hasht)))
		return ; //error         //input-> into void *data ok?
	input->nbrofrooms++;
}

int		rooms(t_lemin *input, int k, char *line)
{
	t_rooms *tmp;
	t_links *lks;

	//	printf("\tEntering rooms! \n");
	// error handling for "a" ?

	if (k <= 0 || (!(tmp = malloc(sizeof(t_rooms)))))
		return (-1);
	else if (line[0] == '#')
	{
		if (!(ft_strcmp(line, "##start"))) //return value 0 if same?
		{
			input->startend = 1;
		}
		else if (!(ft_strcmp(line, "##end")))
		{
			input->startend = 2;
		}
	}
	else
	{
		if ((input->ro = (lm_strsplit(line, ' ', 3))))
		{
			split(input, tmp, lks, input->ro);
			input->startend = 0;
		}
		else if (ft_strrchr(line, '-'))
		{
			input->g++;
			g_process[input->g].f(input, k, line);
		}
		else
		{
			//error check - if room name is different but x, y is same! (new func)
			printf("error\n");
			exit(1);
		}
		//if not 3 words, error, alter return for struct char*/int/int
	}
	return (0);
}

int		linkcheck(t_links *linx, char *dupecheck)
{
	t_links *tmp;

	tmp = linx;
	while (tmp)
	{
		//		printf("linecheck A: %s, dupe: %s\n", tmp->link, dupecheck);
		if (dupecheck == tmp->link)
			return (1);
		tmp = tmp->next;
	}
	//	printf("linecheck B: dupe: %s\n", dupecheck);
	return (0);
}

int		links(t_lemin *input, int k, char *line)
{
	t_links				*newlinka;
	t_links				*newlinkb;
	t_hashlst			*room_one;
	t_hashlst			*room_two;

	//	printf("\tEntering links! \n");
	if (k <= 0)
		return (-1);
	if ((input->ro = (lm_strsplit(line, '-', 2))))
	{
		//		printf("test0 : %s\n", input->ro[0]);
		//		printf("test1 : %s\n", input->ro[1]);
		//		room_one = hash_lookup(input->ro[0], input->hasht);
		//		room_two = hash_lookup(input->ro[1], input->hasht);

		if (!(room_one = hash_lookup(input->ro[0], input->hasht)) ||
				(!(room_two = hash_lookup(input->ro[1], input->hasht))))
		{
			printf("ERROR\n");
			return (-1);
		}	// -1 = error


		//----- iterate through to compare if link already exists
		//if exists return (0); to exit
		//else add new link

		if (!(linkcheck(((t_rooms *)room_one->data)->linx, ((t_rooms *)room_two->data)->name)))
		{

			//			printf("Room1 key----------%s\n", room_one->key);
			//			printf("Room2 key----------%s\n", room_two->key);
			//			printf("Room1 ht: %s\n", ((t_rooms *)(input->hasht->hashtab[hashix(input->ro[0])]->data))->name);
			//			printf("Room2 ht: %s\n", ((t_rooms *)(input->hasht->hashtab[hashix(input->ro[1])]->data))->name);

			//			printf("Room1----------%s\n", ((t_rooms *)(room_one->data))->name);
			//			printf("X----------%d\n", ((t_rooms *)(room_two->data))->x);
			//			printf("Y----------%d\n", ((t_rooms *)(room_two->data))->y);
			//			printf("Dist----------%d\n", ((t_rooms *)(room_two->data))->dist);
			//			printf("Room2----------%s\n", ((t_rooms *)(room_two->data))->name);

			//		exit(1);
			//		printf("Head link: %s\n", head->link);
			if (!(newlinka = malloc(sizeof(t_links))) ||
					(!(newlinkb = malloc(sizeof(t_links)))))
				return (-1);

			newlinka->link = ((t_rooms *)room_two->data)->name;
			newlinka->next = ((t_rooms *)room_one->data)->linx;
			((t_rooms *)(room_one->data))->linx = newlinka;

			//			printf("Head Input: %s\n", ((t_rooms *)(input->hasht->hashtab[hashix(input->ro[0])]->data))->linx->link);
			//		printf("Head link: %s\n", head->link);
			//			printf("---REST AREA---\n");

			newlinkb->link = ((t_rooms *)(room_one->data))->name;
			newlinkb->next = ((t_rooms *)(room_two->data))->linx;
			((t_rooms *)(room_two->data))->linx = newlinkb;

			//		printf("Head link: %s\n", head->link);
			char *str;
			str = ((t_rooms *)(room_two->data))->name;
			//			printf("Head Input: %s\n", ((t_rooms *)(input->hasht->hashtab[hashix(input->ro[1])]->data))->linx->link);
			//		split(input, input->ro, 3);
		}
		else
		{
			printf("ELSE\n");
			//error
		}
	}
	return (0);
}

//static void		roominit(t_lemin *input)

static int		init(t_lemin *input)
{
	//	if (!(input->room = malloc(sizeof(t_rooms) * 1)) ||
	//		(!(input->room->linx = malloc(sizeof(t_links) * 1))))
	//			return (0);
	input->g = 0;
	input->state = 0;
	input->nbrofrooms = 0;
	input->ants_in = 0;
	input->ants_out = 0;
	//	input->in_paths = 0;
	//	input->out_paths = 0;
	input->startend = 0;
	input->roomhead = NULL;
	input->anthead = NULL;
	input->anttail = NULL;
	input->hasht = hash_newtab();
	//	input->usedpath = hash_newtab();
	return (1);
}

//maximum coordinate 1k, 1k
//checks to see if more than 1 room occupies 1 set of coordinates
//if same hash and same coord, but diff name = failed errorcheck
int		roomdupcheck(char *name, int x, int y) //what other input?
{
	static unsigned int	tab[1000][1000];
	static int			state;
	int					i;
	int					j;

	i = -1;
	j = -1;
	state = 0;
	if (!state)
		while (++i <= 1000)
			while (++j <= 1000)
				tab[i][j] = 0;
	state = 1;
	if (!tab[x][y])
		tab[x][y] = hashix(name);
	else
		if (tab[x][y] != hashix(name))
			return (0);	//error! two rooms occupy same coordinate!
	return (1);
}

void		test_output(t_lemin *input, t_rooms *head)
{
	t_rooms		*r_tmp;
	t_links		*l_tmp;

	printf("TEST OUTPUT COMMENCE: \n");
	r_tmp = head;
	while (r_tmp)
	{
		printf("%s - dst: %d  Neighbors:\n", r_tmp->name, r_tmp->dist);
		l_tmp = r_tmp->linx;
		while (l_tmp)
		{
			printf("\t%s\n", l_tmp->link);
			l_tmp = l_tmp->next;
		}
		r_tmp = r_tmp->next;
	}
	//	printf("Address Start %x\n", input->start);
	//	printf("Address Start %x\n", input->end);
	//	printf("START: %s - dst: %d  Neighbors:\n", input->start->name, input->start->dist);
	//	printf("END: %s - dst: %d  Neighbors:\n", input->end->name, input->end->dist);
}

int			main()
{
	t_lemin *input;
	int		k;
	char	*line;

	k = 0;
	if (!(input = malloc(sizeof(t_lemin) * 1)) || (!(init(input))))
		return (-1);
	while ((k = get_next_line(0, &line)))
	{
		//	printf("\tinput->g:%d\t", input->g);
		//	printf("\t%s\n", line);
		if (g_process[input->g].f(input, k, line) == -1)
		{
			printf("Error\n");
			exit(1);
		}
	}
	input->g++;
	while (input->g <= 4)
	{

		//		test_output(input, input->roomhead);
		if (g_process[input->g].g(input) == -1)
		{
			printf("Error\n");
			exit(1);
		}
		input->g++;
	}
	//	test_output(input);
	return (0);
}