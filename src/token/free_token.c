/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:24:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/19 23:31:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void			free_token(t_token **token)
{
	if (*token == NULLTOKEN)
		return ;
	free_token(&(*token)->next);
	free(*token);
	*token = NULLTOKEN;
}