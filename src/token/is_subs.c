/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_subs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:57:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/12 19:29:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int			ft_isnull(t_param *param)
{
	return ((param->buff[param->i] == 0));
}

int			ft_isbracket(t_param *param)
{
	return ((param->buff[param->i] == '{'));
}

int			ft_isparen(t_param *param)
{
	return ((param->buff[param->i] == '('));
}

int			ft_isnameend(t_param *param)
{
	return (!ft_isalnum(param->buff[param->i]));
}

int			ft_isbackquote(t_param *param)
{
	return ((param->buff[param->i] == '`'));
}
