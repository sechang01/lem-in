/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 10:32:09 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:08:35 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		inner_process_o(t_flag *mods, char *x, unsigned long *len)
{
	if (mods->flag[1] > 0 && x[0] != '0')
		(*len)++;
	if (!mods->flag[3])
		(*len > mods->preci) ? width_n_c(mods, *len, 'n') : width_n_c(\
			mods, mods->preci, 'n');
	*len = preci(mods, *len);
	if (mods->flag[1] > 0 && x[0] != '0')
		mods->store->buf[mods->i++] = '0';
	while (*x)
		mods->store->buf[mods->i++] = *x++;
	if (mods->flag[3] > 0)
		width_n_c(mods, *len, 'n');
}

void			printf_o(t_flag *mods)
{
	char			*x;
	unsigned long	len;

	if (mods->flag[11] == 1)
		x = ouxx(mods, 8, 'a');
	else
		x = (mods->flag[10] == 'O') ? itoabase((unsigned long long)
			va_arg(mods->vg, unsigned long), 8, 'a') : itoabase((unsigned int)
			va_arg(mods->vg, unsigned int), 8, 'A');
	len = (unsigned long)ft_strlen(x);
	if (len == 1 && x[0] == '0' && !mods->flag[11] && !mods->flag[4] &&
			!mods->preci && !mods->flag[1])
	{
		if (!mods->width && !mods->preci && mods->flag[0] > 0 &&
				!mods->flag[1])
			return ;
		else if (mods->width > 0 && !mods->preci && mods->flag[0] > 0)
			x[0] = ' ';
	}
	inner_process_o(mods, x, &len);
	free(x);
}
