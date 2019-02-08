/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/02/07 06:54:51 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "struct.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

char			*get_line(int fd);
void			free_tab(char ***tabl);
int				get_tab_len(char **tabl);
char			**ft_ralloc(char ***env, int len);

void			ft_setenv(char ***env, char *new, int len);
char			*get_env(char **env, char *to_get);
char			**collect_env(char **ep);

/*
**	Select, copy, cut and paste
*/

void			select_left(t_line *line);
void			select_right(t_line *line);

void			select_up(t_line *line);
void			select_down(t_line *line);

void			ft_copy(t_line *line);
void			ft_paste(t_line *line);
void			ft_cut(t_line *line);

/*
**	Heredoc
*/

int				deal_hdoc(t_line *line);
int				deal_continue(t_line *line);
void			change_state(t_line *line, int state);

int				check_hdoc(t_line *line);

/*
** Completion
*/
void			feed_tree(char *str, unsigned char type,
		t_tree **tern, int lvl);
t_tree			*create_bin_tree(char **env);
t_tree			*create_env_tree(char **env);
t_tree			*create_file_tree(char *path, t_tree *tern);

void			set_psblty(t_tree *tern);
void			*free_tree(t_tree *tern);
void			free_all_tree(t_line *line);

void			reset_put(t_tree *tern);
void			deal_reset(t_tree **tree);

/*
** Globing
*/

t_slst			*deal_globing(char *str, t_tree *tree);

/*
** Signals
*/

void			set_signal(void);

/*
**	Reset line
*/

void			put_new_prompt(t_line *line);
void			del_all_state(t_line *line);
void			free_hdoc(t_line *line);
void			reset_hist(t_line *line);

void			put_prompt(char *prompt);

char			*remove_line_continuation(char *line);

void			free_buff(t_line *line);
t_line			*get_struct(void);
void			free_struct(t_line *line);
void			del_all_state(t_line *line);

#endif
