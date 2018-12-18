/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/18 04:43:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator.h"
#include "parser.h"

static t_m_list		*new_m_list(t_token *token, t_m_list **list)
{
	if (!token || token->type == UNDEFINED)
		return (NULLLIST);
	if ((*list = ft_memalloc(sizeof(**list))) == NULLLIST)
		return (NULLLIST);
	if (token->spec == BACKGRND)
		(*list)->mode = token->spec;
	else
		(*list)->mode = SEMI;
	return (*list);
}

static t_ao_list	*new_ao_list(t_token *token, t_ao_list **aolist)
{
	if ((*aolist = ft_memalloc(sizeof(**aolist))) == NULLAOLIST)
		return (NULLAOLIST);
	if (token->spec == OR_IF || token->spec == AND_IF)
		(*aolist)->mode = token->spec;
	return (*aolist);
}

static void			*new_command(void **cmd)
{
	if ((*cmd = ft_memalloc(sizeof(t_command))) == NULL)
		return (NULLCOMMAND);
	((t_command *)(*cmd))->type = IS_COMMAND;
	return (cmd);
}

static void			**new_pipe(void **cmd)
{
	t_pipeline		*pipe;

	if (*cmd == NULL)
		return (NULL);
	if ((pipe = ft_memalloc(sizeof(*pipe))) == NULLPIPE)
		return (NULL);
	pipe->type = IS_PIPE;
	if (((t_command *)(*cmd))->type == PIPE)
	{
		pipe->left = *cmd;
		*cmd = pipe;
	}
	else
		pipe->left = *cmd;
	return (&pipe->right);
}

static t_argument	**new_argument(t_token *token, t_argument **arg)
{
	if ((*arg = ft_memalloc(sizeof(**arg))) == NULLARG)
		return (NULL);
	(*arg)->token = token;
	return (&(*arg)->next);
}

static t_redirection	**new_redirection(t_token **token, t_redirection **red)
{
	if (*red == NULLREDIR && (*red = ft_memalloc(sizeof(**red))) == NULLREDIR)
		return (NULL);
	(*red)->token = *token;
	(*red)->arg = (*token)->next;
	if ((*token)->next == NULL)
		return (NULL);
	*token = (*token)->next;
	if ((*token)->type != TOKEN
		|| ((*token)->spec != WORD && (*token)->spec != NAME))
		return (NULL);
	return (&(*red)->next);
}

static t_redirection	**new_ionumber(t_token *token, t_redirection **red)
{
	if ((*red = ft_memalloc(sizeof(**red))) == NULLREDIR)
		return (NULL);
	(*red)->ionumber = token;
	return (&(*red)->next);
}

t_m_list			*parse(const char *buff, t_token *token)
{
	t_m_list		*lhead;
	t_m_list		*ltail;
	t_ao_list		*aolist;
	void			**cmd;
	t_argument		**arg;
	t_redirection	**redir;

	if ((ltail = new_m_list(token, &lhead)) == NULLLIST)
		return (parse_error(buff, token, lhead));
	if ((aolist = new_ao_list(token, &lhead->aolist)) == NULLAOLIST)
		return (parse_error(buff, token, lhead));
	if ((cmd = new_command(&aolist->cmd)) == NULL)
		return (parse_error(buff, token, lhead));
	arg = &((t_command *)*cmd)->args;
	redir = &((t_command *)*cmd)->redir;
	while (token)
	{
		if (token->type == OPERATOR && IS_LIST(token->spec))
		{
			if (token->spec == BACKGRND && aolist->cmd == NULLCOMMAND)
				return (parse_error(buff, token, lhead));
			if ((ltail = new_m_list(token->next, &ltail->next)) == NULLLIST)
				return (parse_error(buff, token, lhead));
			if ((aolist = new_ao_list(token, &ltail->aolist)) == NULLAOLIST)
				return (parse_error(buff, token, lhead));
			if ((cmd = new_command(&aolist->cmd)) == NULL)
				return (parse_error(buff, token, lhead));
			arg = &((t_command *)*cmd)->args;
			redir = &((t_command *)*cmd)->redir;
		}
		else if (token->type == OPERATOR && IS_AOLIST(token->spec))
		{
			if (aolist->cmd == NULLCOMMAND)
				return (parse_error(buff, token, lhead));
			if ((aolist = new_ao_list(token, &aolist->next)) == NULLAOLIST)
				return (parse_error(buff, token, lhead));
			if ((cmd = new_command(&aolist->cmd)) == NULL)
				return (parse_error(buff, token, lhead));
			arg = &((t_command *)*cmd)->args;
			redir = &((t_command *)*cmd)->redir;
		}
		else if (token->type == OPERATOR)
		{
			if (token->spec == PIPE)
			{
				if ((cmd = new_pipe(cmd)) == NULL)
					return (parse_error(buff, token, lhead));
				arg = &((t_command *)*cmd)->args;
				redir = &((t_command *)*cmd)->redir;
			}
			else
			{
				if ((redir = new_redirection(&token, redir)) == NULL)
					return (parse_error(buff, token, lhead));
			}
		}
		else
		{
			if (token->spec == IO_NUMBER)
			{
				if ((redir = new_ionumber(token, redir)) == NULL)
					return (parse_error(buff, token, lhead));
			}
			else if (token->spec != NEWLINE
				&& (arg = new_argument(token, arg)) == NULL)
				return (parse_error(buff, token, lhead));
		}
		token = token->next;
	}
#ifdef DEBUG
	printf("\nPARSER--------------------------\n");
	debug_parser(buff, lhead);
	printf("-------------------------------END\n");
#endif
	return (lhead);
}
