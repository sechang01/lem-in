/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linkedlist.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 21:03:05 by sechang           #+#    #+#             */
/*   Updated: 2019/03/04 14:37:43 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LINKEDLIST_H
# define FT_LINKEDLIST_H
# include <stdio.h>
# include <stdlib.h>

typedef struct		s_sqnode
{
	void			*data;
	struct s_sqnode	*next;
}					t_sqnode;

typedef struct		s_queue
{
	t_sqnode		*front;
	t_sqnode		*rear;
	int				size;
}					t_queue;

typedef struct		s_stack
{
	t_sqnode		*top;
	int				size;
}					t_stack;

t_stack				*stack_init_lst(void);
int					stack_in(t_stack *lst, void *data);
void				*stack_out(t_stack *lst);
void				stack_print(t_stack *lst);

t_queue				*queue_init_lst(void);
int					queue_in(t_queue *lst, void *data);
void				*queue_out(t_queue *lst);
void				*queue_out_rear(t_queue *lst);
void				queue_print(t_queue *lst);

#endif
