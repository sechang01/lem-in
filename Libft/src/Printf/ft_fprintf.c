/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 11:34:31 by sechang           #+#    #+#             */
/*   Updated: 2018/09/20 11:39:41 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "dispatch.h"

int				ft_fprintf(int fd, const char *s, ...)
{
	t_flag			*mods;
	unsigned long	len;

	if (!(mods = (t_flag *)malloc(sizeof(t_flag))))
		return (0);
	va_start(mods->vg, s);
	len = (store_to_buf((char *)s, mods));
	write(fd, mods->store->buf, mods->store->len);
	free(mods->store);
	free(mods);
	return (len);
}
