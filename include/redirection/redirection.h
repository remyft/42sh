/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 01:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/08 23:44:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "shell_env.h"
# include "parser.h"

# define REDIR_INPUT		{ "<", redirect_input }
# define REDIR_OUTPUT1		{ ">", redirect_output1 }
# define REDIR_OUTPUT2		{ ">|", redirect_output2 }
# define REDIR_OUTPUT_APP	{ ">>", append_redirect_output }
# define REDIR_HERE_DOC		{ "<<", redirect_here_doc }
# define DUPLICATE_INPUT	{ "<&", duplicate_input }
# define DUPLICATE_OUTPUT	{ ">&", duplicate_output }
# define REDIR_RD_WR		{ "<>", redirect_read_write }

typedef struct	s_redir
{
	char		*value;
	int			(*handler)(t_redirection *);
}				t_redir;

int				redirection(const char *buff, t_redirection *redir, t_s_env *e);

int				redirect_input(t_redirection *redir);
int				redirect_output1(t_redirection *redir);
int				redirect_output2(t_redirection *redir);
int				append_redirect_output(t_redirection *redir);
int				redirect_here_doc(t_redirection *redir);
int				duplicate_input(t_redirection *redir);
int				duplicate_output(t_redirection *redir);
int				redirect_read_write(t_redirection *redir);

#endif
