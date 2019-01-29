/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:51:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/29 12:59:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

#ifndef DEBUG

void			debug_expansion(char *name, t_ret *ret)
{
	(void)name;
	(void)ret;
}

#else

void			debug_expansion(char *name, t_ret *ret)
{
	int			i;

	i = 0;
	ft_putstr(name);
	ft_putstr(" word: ");
	ft_putendl(ret->word);
	i = 0;
	ft_putstr(name);
	ft_putstr(" subs: ");
	ft_putendl(ret->substitute);
}

#endif
