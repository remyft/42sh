/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 12:24:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 12:53:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/*
** The if checks the that '=' character is:
**  - the first word in list
**  - the previous token is an assignment word too
**  - if the name is valid
*/

t_token			*handle_equal(t_param *param, t_call *token)
{
	(void)token;
	if (param->token->type == UNDEFINED)
		param->token->type = WORD;
	else if ((!param->token->prev || param->token->prev->id == ASSIGNMENT_WORD)
		&& ft_isvalidname(param))
		param->token->id = ASSIGNMENT_WORD;
	return (param->token);
}
