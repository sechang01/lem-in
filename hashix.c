/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:22:27 by sechang           #+#    #+#             */
/*   Updated: 2019/03/15 21:34:22 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "hashix.h"

unsigned int			hashix(char *key)
{
	unsigned int		hashval;
	unsigned int		i;

	i = 0;
	hashval = 0;
	while (key[i])
	{
		hashval += (unsigned int)key[i] + 31 * hashval;
		i++;
	}
	return (hashval % HASHSIZE);
}

t_hashlst				*hash_lookup(char *key, t_hasharr *arr)
{
	t_hashlst			*np;

	np = arr->hashtab[hashix(key)];
	while (np)
	{
		if (ft_strcmp(key, np->key) == 0)
		{
			return (np);
		}
		np = np->next;
	}
	return (NULL);
}

t_hashlst				*hash_install(char *key, void *data, t_hasharr *arr)
{
	t_hashlst			*np;
	unsigned int		hashval;

	if ((np = hash_lookup(key, arr)) == NULL)
	{
		np = (t_hashlst *)malloc(sizeof(*np));
		if (np == NULL || (np->key = ft_strdup(key)) == NULL)
			return (NULL);
		hashval = hashix(key);
		np->next = arr->hashtab[hashval];
		arr->hashtab[hashval] = np;
	}
	else
	{
		return (NULL);
	}
	if ((np->data = data) == NULL)
	{
		return (NULL);
	}
	return (np);
}

t_hasharr				*hash_newtab(void)
{
	int					i;
	t_hasharr			*new;

	if (!(new = (t_hasharr *)malloc(sizeof(t_hasharr))))
		return (NULL);
	i = -1;
	while (++i <= HASHSIZE)
		new->hashtab[i] = NULL;
	return (new);
}

t_hasharr				*hash_wipe(t_hasharr *htab)
{
	int					i;

	i = 0;
	while (i < HASHSIZE)
		htab->hashtab[i++] = NULL;
	return (htab);
}
