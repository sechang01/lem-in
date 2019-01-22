/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 10:31:28 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:08:12 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		inner_process_u(t_flag *mods, char *x, unsigned long *len,
						unsigned long *newlen)
{
	if (mods->preci > *len)
		*newlen = *newlen + (mods->preci - *len);
	if (mods->flag[3] == 0)
		width_n_c(mods, *newlen, 'n');
	*len = preci(mods, *len);
	while (*x)
		mods->store->buf[mods->i++] = *x++;
	if (mods->flag[3] > 0)
		width_n_c(mods, *len, 'n');
}

void			printf_u(t_flag *mods)
{
	char			*x;
	unsigned long	len;
	unsigned long	newlen;

	x = NULL;
	if (mods->flag[10] == 'U')
		x = itoabase(va_arg(mods->vg, unsigned long long), 10, 'a');
	else if (mods->flag[11] == 1)
		x = ouxx(mods, 10, 'a');
	else if (mods->flag[10] == 'u')
		x = itoabase(va_arg(mods->vg, unsigned int), 10, 'a');
	len = (unsigned long)ft_strlen(x);
	if (len == 1 && x[0] == '0' && !mods->flag[11] && !mods->flag[4]
		&& mods->preci == 0 && mods->flag[1] == 0)
	{
		if (!mods->width && !mods->preci && mods->flag[0] > 0 &&
				!mods->flag[1])
			return ;
		else if (mods->width > 0 && !mods->preci && mods->flag[0] > 0)
			x[0] = ' ';
	}
	newlen = len;
	inner_process_u(mods, x, &len, &newlen);
	free(x);
}
