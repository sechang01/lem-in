/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:56:31 by sechang           #+#    #+#             */
/*   Updated: 2019/03/23 06:02:32 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_links		*lm_mergesort(t_links **headref, t_lemin *input)
{
	t_links	*head;
	t_links	*a;
	t_links	*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return (head);
	frontbacksplit(head, &a, &b);
	lm_mergesort(&a, input);
	lm_mergesort(&b, input);
	*headref = sortedmerge(a, b, input);
	return (*headref);
}

t_links		*sortedmerge(t_links *a, t_links *b, t_lemin *input)
{
	t_links *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (((t_rooms *)hash_lookup(a->link, input->hasht)->data)->dist <=
		((t_rooms *)hash_lookup(b->link, input->hasht)->data)->dist)
	{
		result = a;
		result->next = sortedmerge(a->next, b, input);
	}
	else
	{
		result = b;
		result->next = sortedmerge(a, b->next, input);
	}
	return (result);
}

void		frontbacksplit(t_links *source, t_links **frontref, t_links **backref)
{
	t_links	*fast;
	t_links	*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontref = source;
	*backref = slow->next;
	slow->next = NULL;
}