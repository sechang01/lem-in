/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 00:28:23 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 00:03:22 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "Libft/inc/libft.h"
# include "hashix.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_links
{
//	int				crossed;
	char			*link;
	struct s_links	*next;
}					t_links;

typedef struct		s_rooms
{
	char			*name;
	int				x;
	int				y;
	t_links			*linx;
	int				dist;
	int				occupied;

//	struct s_rooms	*intent; // del
//	struct s_rooms	*p_me;	// del

//	int				counter;
//	t_links			*crossed;
//	struct s_rooms	*collision;
//	int				dist_diff;
//	int				stuck;
//	struct s_rooms *begin_path;

//	int				male;
//	int				female;
	
	int				pathnbr;
	int				bfs;

	struct s_rooms	*next;
}					t_rooms;
/*
typedef struct		s_turns
{
	int				turn;
	struct s_rooms	*collision;
	struct s_turns	*next;
}					t_turns;
*/
typedef struct		s_lemin
{
	int				g;
	int				state;
	int				blockstate;
	int				nbrofrooms;
	int				antnum;
	int				ants_in;
	int				ants_out;
//	int				in_cpy;
//	int				out_cpy;
	int				ants_searching;
	int				startend;
	char			**ro;
	t_rooms			*start;
	t_rooms			*end;
//	t_rooms			*lstcopy;
//	t_rooms			*i_tmp;
	t_rooms			*roomhead;
	t_rooms			*prevroom;
	t_rooms			*anthead;
	t_rooms			*anttail;
//	t_rooms			*tmp;
	t_hasharr		*hasht;
	t_rooms			*closest;
//	t_rooms			*pme_lst;
	int				turn;
//	int				in_paths;
//	int				out_paths;
//	int				entrances;
//	int				startpathkey;
	int				thkey;
	char			usage;
//	int				bneck;
//	int				tries;
	int				paths_taken;
	int				best_turn;
//	int				blocked;
	int				pathnbr;
	int				path_dist;
	int				best_dist;
	int				startnbr;
}					t_lemin;

typedef struct		s_process
{
	int				state;
	int				(*f)(t_lemin *x, int k, char *line);
	int				(*g)(t_lemin *x);
}					t_process;

int					ants_in(t_lemin *input, int k, char *line);
int					rooms(t_lemin *input, int k, char *line);
int					links(t_lemin *input, int k, char *line);
char				**lm_strsplit(char const *s, char c, int numwords);
char				**lm_getwords(char const *s, char c, int numwords);
void				split(t_lemin *input, t_rooms *tmp, t_links *lks,
					char **splitee);
int					linkcheck(t_links *linx, char *dupecheck);
int					roomdupcheck(char *name, int x, int y);
int					room_dist(t_lemin *input);
int					gogo_ants(t_lemin *input);
static int			gogo_ants2(t_lemin *input);
t_rooms				*closest_node(t_lemin *input, t_rooms *curr,
					int hstate, int tstate);
t_rooms				*closest_node2(t_lemin *input, t_rooms *curr);
void				start_nexus(t_lemin *input);
void				test_output(t_lemin *input, t_rooms *head);
int					array_o_ants(t_lemin *input);
void				error_exit(int key);
void				start_path_check(t_lemin *input, t_rooms *curr);
void				usage_flags(t_lemin *input, t_rooms *r);
void				print_usage(t_lemin *input, t_rooms *r);
t_links				*lm_mergesort(t_links **headref, t_lemin *input);
t_links				*sortedmerge(t_links *a, t_links *b, t_lemin *input);
void				frontbacksplit(t_links *source, t_links **frontref, t_links **backref);
void				sort_neighbors_dist(t_lemin *input);
int					gogo_ants_start(t_lemin	*input);
int					testf(t_lemin *input);

static t_process	g_process[] = \
{
	{0, &ants_in, NULL},
	{1, &rooms, NULL},
	{2, &links, NULL},
	{3, NULL, &room_dist},
	{4, NULL, &testf},
	{5, NULL, &gogo_ants_start},
	{0, 0}
};

#endif
