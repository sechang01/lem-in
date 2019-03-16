/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 13:09:44 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:40:32 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashix.h"
#include "lem_in.h"

static int		init(t_lemin *input, char *argv)
{
	input->g = 0;
	input->state = -1;
	input->nbrofrooms = 0;
	input->ants_in = 0;
	input->ants_out = 0;
	input->startend = 0;
	input->start = NULL;
	input->end = NULL;
	input->roomhead = NULL;
	input->anthead = NULL;
	input->anttail = NULL;
	input->hasht = hash_newtab();
	input->startpathkey = 1;
	input->usage = '\0';
	if (argv && (!ft_strcmp(argv, "-t")))
		input->usage = 't';
	else if (argv && (!ft_strcmp(argv, "-n")))
		input->usage = 'n';
	else if (argv && (!ft_strcmp(argv, "-d")))
		input->usage = 'd';
	else if (argv && (!ft_strcmp(argv, "-b")))
		input->usage = 'b';
	else if (argv)
		error_exit(0);
	return (1);
}

void			error_exit(int key)
{
	if (key == 1)
		ft_printf("Error\n");
	else if (key == 2)
		ft_printf("Valid Path Not Found\n");
	else
		ft_printf("usage: ./lem-in [-tbnd] < mapfile\
				\n-t: Display number of turns.\
				\n-b: Display basic info.\
				\n-n: Display all rooms and their neighbors.\
				\n-d: Display all rooms with their distance \
				from end and occupied states.\n");
	exit(1);
}

int				main(int argc, char **argv)
{
	t_lemin		*input;
	int			k;
	char		*line;

	if (argc > 1 && argv[1][0] != '-')
		error_exit(0);
	k = 0;
	if (!(input = malloc(sizeof(t_lemin) * 1)) || (!(init(input, argv[1]))))
		error_exit(1);
	while ((k = get_next_line(0, &line)))
		if (g_process[input->g].f(input, k, line) == -1)
			error_exit(1);
	if (input->g != 2)
		error_exit(1);
	input->g++;
	if (!input->nbrofrooms || !input->start || !input->end ||
			(!(ft_strcmp(input->start->name, input->end->name))))
		error_exit(1);
	while (input->g <= 4)
	{
		if (g_process[input->g].g(input) == -1)
			error_exit(1);
		input->g++;
	}
	return (0);
}
