/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:50:35 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/22 03:11:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUT_H
# define PUT_H

# include "struct.h"

void	get_isput(t_slct *select, int len, int lvl, int *tres);
void	reset_isput(t_slct *select, int len, int lvl);
void	get_psb(t_slct *select, int len, int lvl, int *psb);
int		ret_psb(t_slct *select, int len, int lvl, char *bru);
void	put_select(t_slct *select, int lvl);

void	get_max_len(t_tree *curr, int *lenm);
void	get_put(t_tree *tern, int *ret, char c);
int		get_tstr(t_tree *tern, char *str);

#endif
