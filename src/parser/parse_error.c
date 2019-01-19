/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:11:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/19 00:55:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_error(const char *buff, t_token *token)
{
	ft_putstr_fd("21sh: parse error near `", 2);
	if (token == NULLTOKEN)
		ft_putstr_fd("\\n", 2);
	else
		write(2, buff + token->head, token->tail - token->head);
	ft_putendl_fd("'", 2);
	return (0);
}
