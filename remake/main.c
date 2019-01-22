#include "hashix.h"
#include "lem_in.h"

static int		init(t_lemin *input)
{
	//	if (!(input->room = malloc(sizeof(t_rooms) * 1)) ||
	//		(!(input->room->linx = malloc(sizeof(t_links) * 1))))
	//			return (0);
	input->g = 0;
	input->state = -1;
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
	printf("HERE\n");
	if (!input->nbrofrooms || !input->start || !input->end || input->start == input->end)
	{
		printf("EXIT\n");
		exit(1);
	}
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
