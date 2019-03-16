/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 21:21:40 by sechang           #+#    #+#             */
/*   Updated: 2019/03/03 23:29:58 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linkedlist.h"

t_stack		*stack_init_lst(void)
{
	t_stack		*new;

	if (!(new = (t_stack *)malloc(sizeof(t_stack))))
		return (NULL);
	new->size = 0;
	new->top = NULL;
	return (new);
}

int			stack_in(t_stack *lst, void *data)
{
	t_sqnode	*tmp;

	if (!lst || !(tmp = (t_sqnode *)malloc(sizeof(t_sqnode))))
		return (-1);
	tmp->data = data;
	tmp->next = lst->top;
	lst->top = tmp;
	lst->size++;
	return (1);
}

void		*stack_out(t_stack *lst)
{
	t_sqnode	*tmp;
	void		*tmp2;

	if (!lst || !lst->top)
		return (0);
	tmp2 = lst->top->data;
	tmp = lst->top;
	lst->top = lst->top->next;
	free(tmp);
	lst->size--;
	return (tmp2);
}

void		stack_print(t_stack *lst)
{
	t_sqnode	*tmp;

	if (!lst || !lst->top)
	{
		printf("List empty");
		return ;
	}
	tmp = lst->top;
	while (tmp)
	{
		printf("Void: %s\n", (char *)tmp->data);
		tmp = tmp->next;
	}
}
