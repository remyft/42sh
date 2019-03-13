/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:39:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:41:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_errors.h"
#include "parser.h"

int				parse_list(t_token **token, t_p_param *param, t_s_env *e)
{
	if ((*token)->next && !new_tree(*token, param, &(*param->list)->next))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	return (1);
}
