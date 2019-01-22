/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 12:55:47 by sechang           #+#    #+#             */
/*   Updated: 2018/09/01 13:14:37 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCH_H
# define DISPATCH_H

typedef struct		s_type
{
	char			fmt;
	void			(*f)(t_flag *x);
}					t_type;

static t_type	g_type[] = \
{
	{'c', &printf_c},
	{'C', &printf_c},
	{'s', &printf_s},
	{'S', &printf_big_s},
	{'p', &printf_x},
	{'d', &printf_d},
	{'D', &printf_d},
	{'i', &printf_d},
	{'o', &printf_o},
	{'O', &printf_o},
	{'u', &printf_u},
	{'U', &printf_u},
	{'x', &printf_x},
	{'X', &printf_x},
	{'%', &printf_c},
	{0, 0}
};

static char		*g_hex_upp = "0123456789ABCDEF";
static char		*g_hex_low = "0123456789abcdef";

#endif
