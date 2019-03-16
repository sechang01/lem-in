/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 22:28:32 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 23:28:36 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"

t_queue		*queue_init_lst(void)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->size = 0;
	new->front = NULL;
	new->rear = NULL;
	return (new);
}

int			queue_in(t_queue *lst, void *data)
{
	t_sqnode	*tmp;

	if (!lst)
		return (-1);
	if (!lst->front)
	{
		if (!(lst->front = (t_sqnode *)malloc(sizeof(t_sqnode))))
			return (-1);
		lst->front->data = data;
		lst->front->next = 0;
		lst->rear = lst->front;
		lst->size++;
	}
	else
	{
		if (!(tmp = (t_sqnode *)malloc(sizeof(t_sqnode))))
			return (-1);
		tmp->data = data;
		tmp->next = 0;
		lst->rear->next = tmp;
		lst->rear = tmp;
		lst->size++;
	}
	return (1);
}

void		*queue_out(t_queue *lst)
{
	t_sqnode	*tmp;
	void		*tmp2;

	if (!lst || !lst->front)
		return (0);
	tmp = lst->front;
	tmp2 = lst->front->data;
	lst->front = lst->front->next;
	free(tmp);
	lst->size--;
	return (tmp2);
}

void		*queue_out_rear(t_queue *lst)
{
	t_sqnode	*tmp;
	void		*tmp3;
	int			i;

	if ((i = 1) && (!lst || !lst->front))
		return (0);
	if ((tmp = lst->front) && lst->size == 1)
	{
		tmp3 = lst->front->data;
		lst->front = lst->front->next;
		free(tmp);
	}
	else
	{
		while (i++ < lst->size - 1)
			tmp = tmp->next;
		lst->rear = tmp;
		tmp3 = tmp->next->data;
		tmp = tmp->next;
		free(tmp);
		lst->rear->next = 0;
	}
	lst->size--;
	return (tmp3);
}

void		queue_print(t_queue *lst)
{
	t_sqnode *tmp;

	if (!lst || !lst->front)
	{
		printf("List empty");
		return ;
	}
	tmp = lst->front;
	while (tmp)
	{
		printf("Print Out: %s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
	printf(" ----- \n");
}
