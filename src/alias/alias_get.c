/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/08 05:34:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

t_token				*alias_get(t_token *token, t_alias *alias)
{
	if (!token || !alias)
		return (token);
	return (NULLTOKEN);
}