/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:02:51 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:14:26 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		inner_process(t_flag *mods, char *x, unsigned long long *len,
					unsigned long long *newlen)
{
	if (mods->flag[5] > 0 && mods->flag[4] == 0 && x[0] != '-')
		(*newlen)++;
	if (mods->preci > *len)
		*newlen = *newlen + (mods->preci - *len);
	if (mods->flag[4] > 0 && x[0] != '-')
		(*newlen)++;
	if (!mods->flag[3] && !mods->flag[2] && (mods->width > mods->preci))
		width_n_c(mods, *newlen, 'n');
	if (x[0] == '-')
		mods->store->buf[mods->i++] = *x++;
	else if (mods->flag[4] > 0)
		mods->store->buf[mods->i++] = '+';
	else if (mods->flag[5] > 0)
		mods->store->buf[mods->i++] = ' ';
	if (!mods->flag[3] && mods->flag[2] > 0)
		width_n_c(mods, *newlen, 'n');
	*len = preci(mods, *len);
	if (*x == '-' && !mods->flag[2])
		mods->store->buf[mods->i++] = *x++;
	while (*x)
		mods->store->buf[mods->i++] = *x++;
	if (mods->flag[3] > 0)
		width_n_c(mods, *newlen, 'n');
}

void			printf_d(t_flag *mods)
{
	char					*x;
	unsigned long long		len;
	unsigned long long		newlen;

	x = (mods->flag[10] == 'D') ? imax_itoa(va_arg(mods->vg, long)) : \
		numx(mods);
	len = (unsigned long long)ft_strlen(x);
	if (len == 1 && x[0] == '0' && !mods->flag[11] &&
			!mods->flag[4] && !mods->preci)
	{
		if (mods->flag[0] > 0 && !mods->width)
			return ;
		else if (mods->flag[0] > 0 && !mods->preci)
			x[0] = ' ';
	}
	newlen = len;
	if ((x[0] == '-') && ((mods->preci > mods->width) || (mods->preci > \
			(len - 1))))
		len--;
	inner_process(mods, x, &len, &newlen);
	free(x);
}
