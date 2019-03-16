/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:24:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/08 04:27:16 by gbourgeo         ###   ########.fr       */
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

void			free_quote(t_quote **quote)
{
	if (*quote == NULLQUOTE)
		return ;
	free_quote(&(*quote)->next);
	free(*quote);
	*quote = NULLQUOTE;
}
