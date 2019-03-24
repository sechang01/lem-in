/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 14:21:39 by sechang           #+#    #+#             */
/*   Updated: 2019/03/22 15:30:24 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!s2 || !s1)
		return (0);

//	ft_printf("Comparing: %s with: %s, \n", s1, s2);
	ft_printf("inside strcmp\n");
	while (s1[i] && s2[i])
	{

	ft_printf("inside strcmp loop\n");
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}

	ft_printf("outside strcmp loop\n");
	if (s1[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	if (s2[i])
		return (-1);
	else
		return (0);
}
*/


int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;
//	printf("strcmping\n");
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 && (*us1 == *us2))
	{
//		printf("looping\n");
		us1 += 1;
		us2 += 1;
	}
	return (*us1 - *us2);
}
