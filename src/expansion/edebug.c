/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edebug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:51:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/29 19:00:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

#ifndef DEBUG

void			debug_expansion(char *name, t_ret *ret, t_exp *param)
{
	(void)ret;
	(void)param;
}

#else

void			debug_expansion(char *name, t_ret *ret, t_exp *param)
{
	int			i;

	i = 0;
	while (i++ < param->tabval)
		write(1, "\t", 1);
	ft_putstr(name);
	ft_putstr(" word: ");
	ft_putendl(ret->word);
	i = 0;
	while (i++ < param->tabval)
		write(1, "\t", 1);
	ft_putstr(name);
	ft_putstr(" subs: ");
	ft_putendl(ret->substitute);
}

#endif
