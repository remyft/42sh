/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:24:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 14:51:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void		free_quote(t_quote **quote)
{
	if (*quote == NULLQUOTE)
		return ;
	free_quote(&(*quote)->next);
	free(*quote);
	*quote = NULLQUOTE;
}

void			free_token(t_token **token)
{
	if (*token == NULLTOKEN)
		return ;
	free_token(&(*token)->next);
	free_quote(&(*token)->quote);
	free(*token);
	*token = NULLTOKEN;
}
