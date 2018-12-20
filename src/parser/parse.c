/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/20 06:22:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator.h"
#include "parser.h"
#include "handler.h"

// static void				**new_pipe(void **cmd)
// {
// 	t_pipeline			*ptr;

// 	ptr = (t_pipeline *)*cmd;
// 	if (ptr == NULL || ptr->left == NULL)
// 		return (NULL);
// 	if ((*cmd = ft_memalloc(sizeof(*ptr))) == NULL)
// 		return (NULL);
// 	((t_pipeline *)(*cmd))->type = IS_A_PIPE;
// 	((t_pipeline *)(*cmd))->left = ptr;
// 	return (new_command(&((t_pipeline *)(*cmd))->right));
// }

// static t_redirection	**new_redirection(t_token **token, t_redirection **red)
// {
// 	if (*red == NULLREDIR && (*red = ft_memalloc(sizeof(**red))) == NULLREDIR)
// 		return (NULL);
// 	(*red)->token = *token;
// 	(*red)->arg = (*token)->next;
// 	if ((*token)->next == NULL)
// 		return (NULL);
// 	*token = (*token)->next;
// 	if ((*token)->type != TOKEN
// 		|| ((*token)->spec != WORD && (*token)->spec != NAME))
// 		return (NULL);
// 	return (&(*red)->next);
// }

// static t_redirection	**new_ionumber(t_token *token, t_redirection **red)
// {
// 	if ((*red = ft_memalloc(sizeof(**red))) == NULLREDIR)
// 		return (NULL);
// 	(*red)->ionumber = token;
// 	return (&(*red)->next);
// }

// static t_argument		**new_argument(t_token *token, t_argument **arg)
// {
// 	if ((*arg = ft_memalloc(sizeof(**arg))) == NULLARG)
// 		return (NULL);
// 	(*arg)->token = token;
// 	return (&(*arg)->next);
// }

// t_m_list				*parse(const char *buff, t_token *token)
// {
// 	t_m_list		*lhead;
// 	t_m_list		**ltail;
// 	t_ao_list		**aolist;
// 	void			**cmd;
// 	t_argument		**arg;
// 	t_redirection	**redir;

// 	if (!(ltail = new_m_list(token, &lhead)))
// 		return (parse_error(buff, token, lhead));
// 	if (!(aolist = new_ao_list(token, &(*ltail)->aolist)))
// 		return (parse_error(buff, token, lhead));
// 	if (!(cmd = new_command(&(*aolist)->cmd)))
// 		return (parse_error(buff, token, lhead));
// 	arg = &((t_command *)*cmd)->args;
// 	redir = &((t_command *)*cmd)->redir;
// 	while (token)
// 	{
// 		if (token->type == OPERATOR && IS_LIST(token->spec))
// 		{
// 			if (token->spec == BACKGRND && (*aolist)->cmd == NULLCOMMAND)
// 				return (parse_error(buff, token, lhead));
// 			if (!(ltail = new_m_list(token->next, &(*ltail)->next)))
// 				return (parse_error(buff, token, lhead));
// 			if (!(aolist = new_ao_list(token, &(*ltail)->aolist)))
// 				return (parse_error(buff, token, lhead));
// 			if (!(cmd = new_command(&(*aolist)->cmd)))
// 				return (parse_error(buff, token, lhead));
// 			arg = &((t_command *)*cmd)->args;
// 			redir = &((t_command *)*cmd)->redir;
// 		}
// 		else if (token->type == OPERATOR && IS_AOLIST(token->spec))
// 		{
// 			if ((*aolist)->cmd == NULLCOMMAND)
// 				return (parse_error(buff, token, lhead));
// 			if (!(aolist = new_ao_list(token, &(*aolist)->next)))
// 				return (parse_error(buff, token, lhead));
// 			if (!(cmd = new_command(&(*aolist)->cmd)))
// 				return (parse_error(buff, token, lhead));
// 			arg = &((t_command *)*cmd)->args;
// 			redir = &((t_command *)*cmd)->redir;
// 		}
// 		else if (token->type == OPERATOR)
// 		{
// 			if (token->spec == PIPE)
// 			{
// 				if (!(cmd = new_pipe(cmd)))
// 					return (parse_error(buff, token, lhead));
// 				arg = &((t_command *)*cmd)->args;
// 				redir = &((t_command *)*cmd)->redir;
// 			}
// 			else
// 			{
// 				if (!(redir = new_redirection(&token, redir)))
// 					return (parse_error(buff, token, lhead));
// 			}
// 		}
// 		else
// 		{
// 			if (token->spec == IO_NUMBER)
// 			{
// 				if (!(redir = new_ionumber(token, redir)))
// 					return (parse_error(buff, token, lhead));
// 			}
// 			else if (token->spec != NEWLINE
// 				&& !(arg = new_argument(token, arg)))
// 				return (parse_error(buff, token, lhead));
// 		}
// 		token = token->next;
// 	}
// 	debug_parser(buff, lhead);
// 	return (lhead);
// }

// static int				parse_not(t_token *token, t_param *param)
// {
// 	(void)token;
// 	(void)param;
// 	return (0);
// }

static int				parse_argument(t_token *token, t_p_param *param)
{
	if ((*param->arg = ft_memalloc(sizeof(**param->arg))) == NULLARG)
		return (0);
	(*param->arg)->token = token;
	param->arg = &(*param->arg)->next;
	return (0);
}

static int				parse_io_number(t_token *token, t_p_param *param)
{
	if ((*param->redir = ft_memalloc(sizeof(t_redirection))) == NULLREDIR)
		return (1);
	(*param->redir)->ionumber = token;
	param->redir = &(*param->redir)->next;
	return (0);
}

static int				parse_ao_list(t_token *token, t_p_param *param)
{
	if ((*param->aolist)->cmd == NULLCOMMAND)
		return (1);
	if (!(param->aolist = new_ao_list(token, &(*param->aolist)->next)))
		return (1);
	if (!(param->cmd = new_command(&(*param->aolist)->cmd)))
		return (1);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (0);
}

static int				parse_pipe(t_token *token, t_p_param *param)
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

static int				parse_operator(t_token *token, t_p_param *param)
{
	if (*param->redir == NULLREDIR
		&& !(*param->redir = ft_memalloc(sizeof(**param->redir))))
		return (1);
	(*param->redir)->token = token;
	(*param->redir)->arg = token->next;
	if (token->next == NULL)
		return (1);
	token = token->next;
	if (token->type != TOKEN
		|| (token->spec != WORD
			&& token->spec != NAME))
		return (1);
	token->spec = 0;
	param->redir = &(*param->redir)->next;
	return (0);
}

static int				parse_list(t_token *token, t_p_param *param)
{
	return (new_tree(token, param, &(*param->list)->next));
}

t_token					*parse_loop(t_token *token, t_p_param *param)
{
	static t_p_call		type_token[] = {
		H_ARGUMENT, H_ARGUMENT, H_ARGUMENT, H_NULL, H_IO_NUMBER,
		H_ARGUMENT,
	};
	static t_p_call		type_operator[] = {
		H_NULL, H_AO_LIST, H_PIPE, H_OPERATOR, H_NULL, H_AO_LIST,
		H_LIST, H_LIST, H_NULL, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
	};
	static t_t_p_call	call[] = {
		{ type_token }, { type_operator },
	};

	while (token)
	{
		if (token->type != UNDEFINED
			&& call[token->type].type[token->spec].handler)
			if (call[token->type].type[token->spec].handler(token, param))
				break ;
		token = token->next;
	}
	return (token);
}

t_m_list				*parse2(const char *buff, t_token *token)
{
	t_m_list			*list;
	t_p_param			param;

	if (new_tree(token, &param, &list))
		return (parse_error(buff, token, list));
	if ((token = parse_loop(token, &param)))
		return (parse_error(buff, token, list));
	debug_parser(buff, list);
	return (list);
}
