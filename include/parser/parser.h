/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:59:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/20 22:52:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"

/*
** Structure for arguments
*/
# define NULLARG		(t_argument *)0

typedef struct	s_argument
{
	t_token				*token;
	char				**cmd;
	struct s_argument	*next;
}				t_argument;

/*
** Structure for redirections
*/
# define NULLREDIR		(t_redirection *)0

typedef struct	s_redirection
{
	t_token					*token;
	t_token					*ionumber;
	t_argument				*arg;
	int						fdarg;
	struct s_redirection	*next;
}				t_redirection;

/*
** Structure for commands
** type can be TOKEN for the command and its arguments
** or type can be OPERATOR for the redirections <, >, <&, <<, etc..
*/
enum
{
	IS_A_COMMAND,
	IS_A_PIPE,
};

# define NULLCOMMAND	(t_command *)0

typedef struct	s_command
{
	int				type;
	t_argument		*args;
	t_redirection	*redir;
}				t_command;

/*
** Structure for pipes ( '|' )
*/

# define NULLPIPE		(t_pipeline *)0

typedef struct	s_pipeline
{
	int				type;
	void			*left;
	void			*right;
}				t_pipeline;

/*
** Structure for AND-OR list ( '&&' and '||' )
*/

# define NULLAOLIST		(t_ao_list *)0

typedef struct	s_and_or_list
{
	int						mode;
	void					*cmd;
	struct s_and_or_list	*next;
}				t_ao_list;

/*
** Structure for list ( ';' and '&' )
*/

# define NULLLIST		(t_m_list *)0

typedef struct	s_main_list
{
	int					mode;
	t_ao_list			*aolist;
	struct s_main_list	*next;
}				t_m_list;

/*
** Structure grouping pointers needed for parsing
*/
typedef struct	s_parser_param
{
	t_m_list		**list;
	t_ao_list		**aolist;
	void			**cmd;
	t_argument		**arg;
	t_redirection	**redir;
}				t_p_param;

/*
** Structure grouping functions pointers and their return value
*/
typedef struct	s_param_call
{
	int			(*handler)(const char *, t_token **, t_p_param *);
}				t_p_call;

typedef struct	s_t_p_call
{
	t_p_call	*type;
}				t_t_p_call;

t_m_list		*parse(const char *buff, t_token *token);
int				parse_error(const char *buff, t_token *token);

int				new_tree(t_token *token, t_p_param *param, t_m_list **list);
t_m_list		**new_m_list(t_token *token, t_m_list **list);
t_ao_list		**new_ao_list(t_token *token, t_ao_list **list);
void			**new_command(void **cmd);

int				parse_list(const char *buf, t_token **tok, t_p_param *par);
int				parse_operator(const char *buf, t_token **tok, t_p_param *par);
int				parse_pipe(const char *buf, t_token **tok, t_p_param *par);
int				parse_ao_list(const char *buf, t_token **tok, t_p_param *par);
int				parse_io_number(const char *buf, t_token **tok, t_p_param *par);
int				parse_argument(const char *buf, t_token **tok, t_p_param *par);

void			free_m_list(t_m_list **list);

void			debug_parser(const char *buff, t_m_list *list);

#endif