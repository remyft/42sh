/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:45:53 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/27 12:27:59 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_TOOLS_H
# define MAIN_TOOLS_H

# include "libft.h"
# include "struct.h"

int		is_change;

void	init_line(char **env, t_line *line);
void	deal_key(t_line *line);
void	check_path(t_line *line, char **env);
void	deal_typing(t_line *line);

void	sig_hdlr(int sig);
void	sig_winch(int sig);
void	deal_winch(t_line *line);

#endif
