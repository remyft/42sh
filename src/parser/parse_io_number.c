/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:44:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/15 02:42:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int			parse_io_number(t_token **token, t_p_param *param, t_s_env *e)
{
	if ((*param->redir = ft_memalloc(sizeof(t_redirection))) == NULLREDIR)
		return (parse_error(ERR_MALLOC_FAILED, *token, e));
	(*param->redir)->ionumber = *token;
	return (1);
}
