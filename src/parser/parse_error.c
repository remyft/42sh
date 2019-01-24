/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/23 04:46:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_error(t_token *token)
{
	ft_putstr_fd("21sh: parse error near unexpected token `", 2);
	if (token == NULLTOKEN)
		ft_putstr_fd("\\n", 2);
	else
		write(2, token->head, token->len);
	ft_putendl_fd("'", 2);
	return (0);
}
