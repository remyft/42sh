/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:39:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 02:42:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int				parse_list(t_token **token, t_p_param *param, t_s_env *e)
{
	if (!new_tree(*token, param, &(*param->list)->next))
		return (parse_error(ERR_MALLOC_FAILED, *token, e));
	return (1);
}
