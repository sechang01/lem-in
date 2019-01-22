/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 00:28:23 by sechang           #+#    #+#             */
/*   Updated: 2019/01/19 17:08:12 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "Libft/inc/libft.h"
#include "hashix.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


typedef struct 		s_links
{
	char			*link;
	struct s_links	*next;
}					t_links;

typedef struct 		s_rooms
{
	char			*name;
	int				x;
	int				y;
	t_links			*linx;
	int				dist;
	int				occupied;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_lemin
{
	int				g;
	int				state;
	int				nbrofrooms; // used?
	int				antnum;
	int				ants_in;
	int				ants_out;
	int				startend;
	char			**ro;
	t_rooms			*start;
	t_rooms			*end;
	t_rooms			*lstcopy;
	t_rooms			*i_tmp;
	t_rooms			*roomhead;
	t_rooms			*prevroom;
	t_rooms			*anthead;
	t_rooms			*anttail;
	t_hasharr		*hasht;
	int				turn;
	int				in_paths;
	int				out_paths;
	int				entrances;
}					t_lemin;

typedef struct 		s_process
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
void				split(t_lemin *input, t_rooms *tmp, t_links *lks, char **splitee);
int					linkcheck(t_links *linx, char *dupecheck);
int					roomdupcheck(char *name, int x, int y);
int					room_dist(t_lemin *input);
int					gogo_ants(t_lemin *input);
t_rooms				*closest_node(t_lemin *input, t_rooms *curr);
void				test_output(t_lemin *input, t_rooms *head);
int					array_o_ants(t_lemin *input);

static t_process	g_process[] = \
{
		{0, &ants_in, NULL},
		{1, &rooms, NULL},
		{2, &links, NULL},
		{3, NULL, &room_dist},
//		{4, NULL, &array_o_ants},
		{4, NULL, &gogo_ants},
		{0, 0}
};

#endif