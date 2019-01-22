/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 15:15:24 by sechang           #+#    #+#             */
/*   Updated: 2018/09/20 11:43:07 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "dispatch.h"

void			inner_parse_a(char **s, t_flag *mods)
{
	while (flag_found(*(*s)))
	{
		chrfmt(mods, *(*s), 'a');
		(*s)++;
	}
	while (ft_isdigit(*(*s)))
	{
		mods->width *= 10;
		mods->width += *(*s) - '0';
		(*s)++;
	}
}

void			inner_parse_b(char **s, t_flag *mods)
{
	if (*(*s) == '.' && ((*s)++))
	{
		mods->flag[0]++;
		if (!ft_isdigit(*(*s)))
			mods->flag[0]++;
		while (ft_isdigit(*(*s)))
		{
			mods->preci *= 10;
			mods->preci += *(*s) - '0';
			(*s)++;
		}
		if (mods->preci > 0)
			mods->flag[2] = 0;
	}
	while (len_found(*(*s)))
	{
		chrfmt(mods, *(*s), 'b');
		mods->flag[11] = 1;
		(*s)++;
	}
}

void			parse(char **s, t_flag *mods)
{
	int			g;

	initzero(mods);
	if (*(*s) == '%' && ((*s)++))
	{
		chrfmt(mods, 0, 'c');
		inner_parse_a(s, mods);
		inner_parse_b(s, mods);
		g = 0;
		while (g_type[g].fmt)
		{
			if (*(*s) == g_type[g].fmt)
			{
				mods->flag[10] = g_type[g].fmt;
				g_type[g].f(mods);
			}
			g++;
		}
	}
}

int				store_to_buf(char *s, t_flag *mods)
{
	mods->store = (t_printbuf *)malloc(sizeof(t_printbuf));
	ft_bzero(mods->store->buf, BUFF_SIZE + 1);
	mods->store->len = 0;
	mods->i = 0;
	while (*s)
	{
		if (*s == '/' || *s == '%')
			parse(&s, mods);
		else
			mods->store->buf[mods->i++] = *s;
		if (mods->i >= 9000)
		{
			mods->store->len = ft_strlen(mods->store->buf);
			mods->store->buf[mods->store->len + 1] = '\0';
			write(1, mods->store->buf, mods->store->len);
			mods->i = 0;
			store_to_buf(s, mods);
		}
		s++;
	}
	mods->store->len = mods->i;
	mods->store->buf[mods->store->len + 1] = '\0';
	return (mods->store->len);
}

int				ft_printf(const char *s, ...)
{
	t_flag			*mods;
	unsigned long	len;

	if (!(mods = (t_flag *)malloc(sizeof(t_flag))))
		return (0);
	va_start(mods->vg, s);
	len = (store_to_buf((char *)s, mods));
	write(1, mods->store->buf, mods->store->len);
	free(mods->store);
	free(mods);
	return (len);
}
