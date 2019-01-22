/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 10:32:42 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:09:23 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		inner_process_x(t_flag *mods, char *x, unsigned long *len,
						unsigned long *newlen)
{
	*newlen = *len;
	if ((mods->flag[1] > 0 && x[0] != '0') || mods->flag[10] == 'p')
		*newlen = *newlen + 2;
	if (mods->preci > *len)
		*newlen = *newlen + (mods->preci - *len);
	if (!mods->flag[3] && !mods->flag[2])
		width_n_c(mods, *newlen, 'a');
	if ((mods->flag[1] > 0 && x[0] != '0') || mods->flag[10] == 'p')
	{
		mods->store->buf[mods->i++] = '0';
		if (mods->flag[10] == 'X')
			mods->store->buf[mods->i++] = 'X';
		else if (mods->flag[10] == 'x' || mods->flag[10] == 'p')
			mods->store->buf[mods->i++] = 'x';
	}
	if (!mods->flag[3] && mods->flag[2] > 0)
		width_n_c(mods, *newlen, 'a');
	*len = preci(mods, *len);
	while (*x)
		mods->store->buf[mods->i++] = *x++;
	if (mods->flag[3] > 0)
		width_n_c(mods, *newlen, 'a');
}

void			printf_x(t_flag *mods)
{
	char			*x;
	unsigned long	len;
	unsigned long	newlen;

	if (mods->flag[11] == 1 || mods->flag[10] == 'p')
		x = ouxx(mods, 16, (mods->flag[10] == 'x' || mods->flag[10] ==\
			'p') ? 'a' : 'A');
	else
		x = itoabase((unsigned long long)va_arg(mods->vg, unsigned int), \
			16, mods->flag[10] == 'x' || mods->flag[10] == 'p' ? 'a' : 'A');
	len = (unsigned long long)ft_strlen(x);
	if (len == 1 && x[0] == '0' && !mods->flag[11] &&
			!mods->flag[4] && !mods->preci)
	{
		if (!mods->width && !mods->preci && mods->flag[0] > 0)
			return ;
		else if (mods->width > 0 && !mods->preci && mods->flag[0] > 0)
			x[0] = ' ';
	}
	inner_process_x(mods, x, &len, &newlen);
	free(x);
}
