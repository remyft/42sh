/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 01:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/09 20:38:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "shell_env.h"
# include "parser.h"
# include "operator_types.h"

# define REDIR_LESS			{ LESS,       redirect_less }
# define REDIR_LESS_AND		{ LESS_AND,   redirect_less_and }
# define REDIR_LESS_GREAT	{ LESS_GREAT, redirect_less_great }
# define REDIR_GREAT		{ GREAT,      redirect_great }
# define REDIR_GREAT_PIPE	{ GREAT_PIPE, redirect_great_pipe }
# define REDIR_AND_GREAT	{ AND_GREAT,  redirect_and_great }
# define REDIR_GREAT_AND	{ GREAT_AND,  redirect_great_and }
# define REDIR_DGREAT		{ DGREAT,     redirect_dgreat }
# define REDIR_AND_DGREAT	{ AND_DGREAT, redirect_and_dgreat }
# define REDIR_DGREAT_AND	{ DGREAT_AND, redirect_dgreat_and }
# define REDIR_DLESS		{ DLESS,      redirect_dless }
# define REDIR_TLESS		{ TLESS,      redirect_tless }

typedef struct	s_redir
{
	char		*value;
	int			(*handler)(t_redirection *, t_s_env *);
}				t_redir;

int				redirection(const char *buff, t_redirection *redir, t_s_env *e);

int				redirect_input(t_redirection *redir, t_s_env *e);
int				redirect_output1(t_redirection *redir, t_s_env *e);
int				redirect_output2(t_redirection *redir, t_s_env *e);
int				append_redirect_output(t_redirection *redir, t_s_env *e);
int				redirect_here_doc(t_redirection *redir, t_s_env *e);
int				duplicate_input(t_redirection *redir, t_s_env *e);
int				duplicate_output(t_redirection *redir, t_s_env *e);
int				redirect_read_write(t_redirection *redir, t_s_env *e);

#endif
