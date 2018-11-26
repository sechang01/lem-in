
 91         i = 1;
 92         while (s[i] != ' ' && s[i])
 93             i++;
 94         data->m_y = ft_atoi(s + i);
 95         data->m_x = ft_atoi(s + (i + (data->m_y <= 9 ? 3 :     4)));
 96     }
 97     else if ('0' <= s[0] && s[0] <= '9')
 98         store_map(s, data);
 99     else if (s[0] == 'P' && s[1] == 'i')
100     {
101         store_piece_norm(data, k, s, 1);
102         free(s);
103         return (-1);
104     }
105     free(s);
106     return (0);
107 }
~/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 00:25:11 by sechang           #+#    #+#             */
/*   Updated: 2018/10/29 15:09:08 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int main(int argc, char **argv)
{
	gnl(filler style) 

	input:

	num ants
	\## start
	str-num-num
	until ## end

	str-str
	

	stored

}