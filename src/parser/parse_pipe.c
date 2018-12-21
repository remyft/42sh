/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/20 20:48:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				parse_pipe(t_token *token, t_p_param *param)
{
	t_pipeline			*ptr;

	ptr = (t_pipeline *)(*param->cmd);
	if (ptr == NULL || ptr->left == NULL)
		return (1);
	if ((*param->cmd = ft_memalloc(sizeof(*ptr))) == NULL)
		return (1);
	((t_pipeline *)(*param->cmd))->type = IS_A_PIPE;
	((t_pipeline *)(*param->cmd))->left = ptr;
	if (!(param->cmd = new_command(&((t_pipeline *)(*param->cmd))->right)))
		return (1);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (0);
	(void)token;
}
