/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:29:22 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 00:07:36 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHIX_H
# define HASHIX_H
# include "Libft/inc/libft.h"
# define HASHSIZE 333

typedef struct			s_hashlst
{
	char				*key;
	void				*data;
	struct s_hashlst	*next;
}						t_hashlst;

typedef struct			s_hasharr
{
	t_hashlst			*hashtab[HASHSIZE];
}						t_hasharr;

unsigned int			hashix(char *key);
t_hashlst				*hash_lookup(char *key, t_hasharr *arr);
int						hash_install(char *key, void *data, t_hasharr *arr);
t_hasharr				*hash_newtab(void);
t_hasharr				*hash_wipe(t_hasharr *hashtab);

#endif
