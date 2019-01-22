/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charific.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/19 17:38:34 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:15:14 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			printf_c(t_flag *mods)
{
	unsigned char	x;

	if (mods->flag[10] != '%')
		x = (unsigned char)(va_arg(mods->vg, int));
	else
	{
		mods->preci = 0;
		x = '%';
	}
	if (!x)
		mods->preci = 1;
	if (mods->flag[3] == 0)
		width_n_c(mods, 1, 'n');
	mods->store->buf[mods->i++] = x;
	if (mods->flag[3] > 0)
		width_n_c(mods, 1, 'n');
}

static void		inner_process_s(t_flag *mods, char *tmp,
					unsigned long *len)
{
	char			*x;
	int				i;

	x = NULL;
	i = 0;
	if ((unsigned long)ft_strlen(tmp) == 0)
		*len = 0;
	else
		*len = (mods->flag[0] > 0 && mods->preci < (unsigned long)
			ft_strlen(tmp)) ? mods->preci : (unsigned long)ft_strlen(tmp);
	x = ft_strsub((char const*)tmp, 0, (size_t)(*len));
	if (!mods->flag[3])
		width_n_c(mods, *len, 'c');
	while (x[i])
	{
		mods->store->buf[mods->i++] = x[i];
		i++;
	}
	if (mods->flag[3] > 0)
		width_n_c(mods, *len, 'c');
	free(x);
}

void			printf_s(t_flag *mods)
{
	char			*tmp;
	unsigned long	len;

	if (mods->flag[7] > 0)
	{
		printf_big_s(mods);
		return ;
	}
	tmp = va_arg(mods->vg, char *);
	if (!tmp)
	{
		ft_strcpy(&(mods->store->buf[mods->i]), "(null)");
		mods->i = mods->i + 6;
		return ;
	}
	inner_process_s(mods, tmp, &len);
}

void			printf_big_s(t_flag *mods)
{
	wchar_t		*x;

	x = (va_arg(mods->vg, wchar_t *));
	while (*x)
		mods->store->buf[mods->i++] = *x++;
}
