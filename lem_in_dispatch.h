/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_dispatch.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:14:38 by sechang           #+#    #+#             */
/*   Updated: 2018/10/30 14:33:36 by sechang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_DISPATCH_H
# define LEM_IN_DISPATCH_H

typedef struct s_type
{
	char		state;
	void		(*f)(t_lemin)