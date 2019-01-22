/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 22:22:27 by sechang           #+#    #+#             */
/*   Updated: 2018/11/15 21:34:33 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "hashix.h"

unsigned int			hashix(char *key)
{
	unsigned int		hashval;
	unsigned int		i;

//	printf("hashix begin\n");
//	printf("key: %s \n", key);
	i = 0;
	hashval = 0;
	while (key[i])
	{
//		printf("hashix test\n");
		hashval += (unsigned int)key[i] + 31 * hashval;
		i++;
	//	key++;
	}
	return (hashval % HASHSIZE);
}

t_hashlst				*hash_lookup(char *key, t_hasharr *arr)
{
	t_hashlst			*np;

//	printf("lookup begin\n");
	np = arr->hashtab[hashix(key)];
//	printf("test\n");
//	printf("n: %x\n", (unsigned int)np);
	while (np)
	{
		if (ft_strcmp(key, np->key) == 0)
		{
//			printf("inside\n");
			return (np);
		}
		np = np->next;
	}
	return (NULL);
}

// how to deal with duplicate installs of same key?
t_hashlst				*hash_install(char *key, void *data, t_hasharr *arr)
{
//	t_hasharr			*arr;
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
//		printf("----------------install success\n");
	}
	else
	{
//		printf("----------------------else case\n");
		return (NULL);
	}
//		free((void *)np->data);			// uninstall just data?;
	if ((np->data = data) == NULL)    // strdup void *data?
	{
//		printf("---------------------data null\n");
		return (NULL);
	}
	return (np);
}

t_hasharr			*hash_newtab(void)
{
	int				i;
	t_hasharr		*new;

	if (!(new = (t_hasharr *)malloc(sizeof(t_hasharr))))
		return (NULL);
	i = -1;
	while (++i <= HASHSIZE)
		new->hashtab[i] = NULL;
	return (new);
}

t_hasharr			*hash_wipe(t_hasharr *htab)
{
	int				i;

	i = 0;
	while (i < HASHSIZE)
		htab->hashtab[i++] = NULL;
	return (htab);
}
