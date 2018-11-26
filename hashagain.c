/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashagain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:21:53 by sechang           #+#    #+#             */
/*   Updated: 2018/11/09 23:14:39 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define IN 1

struct nlist
{
	struct nlist *next;
	char *name;
	char *defn;
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned int hash(char *s)
{
	unsigned int hashval;

	hashval = 0;
	while (*s)
	{
		hashval = *s + 31 * hashval;
		s++;
	}
	return (hashval % HASHSIZE);
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	np = hashtab[hash(s)];
	while (np)
	{
		if ((strcmp(s, np->name) == 0)
			return np;
		np = np->next;
	}
	return (NULL);
}

struct nlist *lookup(char *)
char *strdup(char *);

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned int hashval;

	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return (NULL);
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *)np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return (NULL);
	return np;
}

