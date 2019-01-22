/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 01:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/22 07:33:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "shell_env.h"
# include "parser.h"

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
