/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:50:33 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 04:51:56 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_tools.h"

void	sig_hdlr(int sig)
{
	(void)sig;
}

void	sig_winch(int sig)
{
	(void)sig;
	is_change = 1;
}

void	deal_winch(t_line *line)
{
	tgetent(NULL, line->term);
	line->nb_col = tgetnum("co");
	is_change = 0;
}