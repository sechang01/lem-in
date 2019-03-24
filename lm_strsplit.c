/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:28:24 by sechang           #+#    #+#             */
/*   Updated: 2019/03/24 01:05:10 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char			**lm_getwords(char const *s, char c, int numwords)
{
	int			wordcount;
	char		**newarr;

	wordcount = 0;
	while (*s)
	{
		if (((*s != c) && (*(s + 1) == c)) || ((*s != c) && (*(s + 1) == '\0')))
			wordcount++;
		s++;
	}
	if (wordcount != numwords)
		return (NULL);
	if (!(newarr = (char **)malloc(sizeof(char *) * (wordcount + 1))))
		return (NULL);
//	(newarr + wordcount) = NULL;
	return (newarr);
}

char			**lm_strsplit(char const *s, char c, int numwords)
{
	char		**arr_split;
	int			wordstart;
	int			k;
	int			i;

	if (!s)
		return (NULL);
	k = 0;
	i = 0;
	wordstart = -1;
	if (!(arr_split = lm_getwords(s, c, numwords)))
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && wordstart == -1)
			wordstart = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			arr_split[k++] = ft_strsub(s, wordstart, (i - wordstart + 1));
			wordstart = -1;
		}
		i++;
	}
	arr_split[k] = NULL;
	return (arr_split);
}
