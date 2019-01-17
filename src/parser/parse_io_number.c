/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:44:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 20:03:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_io_number(t_token **token, t_p_param *param)
{
	if ((*param->redir = ft_memalloc(sizeof(t_redirection))) == NULLREDIR)
		return (0);
	(*param->redir)->ionumber = *token;
	param->redir = &(*param->redir)->next;
	return (1);
}
