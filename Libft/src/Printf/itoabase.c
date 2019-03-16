/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 20:18:57 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:20:04 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "dispatch.h"

size_t			get_intlen(unsigned long long n, int base)
{
	size_t					i;

	i = 1;
	while (n /= base)
		i++;
	return (i);
}

char			*itoabase(unsigned long long n, int base, char key)
{
	char					*str;
	unsigned long long		n_cpy;
	size_t					len;

	n_cpy = n;
	len = get_intlen(n, base);
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len] = '\0';
	str[--len] = (key == 'A') ? g_hex_upp[n_cpy % (unsigned long long)base] : \
		g_hex_low[n_cpy % (unsigned long long)base];
	while (n_cpy /= (unsigned long long)base)
	{
		str[--len] = (key == 'A') ? g_hex_upp[n_cpy % (unsigned long long)\
			base] : g_hex_low[n_cpy % (unsigned long long)base];
	}
	return (str);
}

size_t			imax_get_intlen(intmax_t n)
{
	size_t					i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*imax_itoa(intmax_t n)
{
	char					*str;
	intmax_t				n_cpy;
	size_t					len;

	if (n == (-9223372036854775807 - 1))
	{
		return (ft_strcpy((char *)malloc(sizeof(char) * 21),
					"-9223372036854775808"));
	}
	n_cpy = n;
	len = imax_get_intlen(n);
	if (n < 0)
	{
		n_cpy = -n;
		len++;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len] = '\0';
	str[--len] = n_cpy % 10 + '0';
	while (n_cpy /= 10)
		str[--len] = n_cpy % 10 + '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
