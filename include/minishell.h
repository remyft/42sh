/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/22 07:21:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "struct.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>

char			**parsing(char *cmd);

void			deal_cmd(char **cmd, char ***env, struct termios *save);

char			*get_line(int fd);
char			*replace_str(char *path, char *src, char *replace);
void			free_tab(char ***tabl);
int				get_tab_len(char **tabl);
char			**ft_ralloc(char ***env, int len);

void			ft_setenv(char ***env, char *new, int len);
char			*get_env(char **env, char *to_get);
void			ft_unsetenv(char ***env, char **unset);
char			**collect_env(char **ep);

void			ft_cd(char ***env, char **cmd);

int				ft_exec(char **env, char **cmd, struct termios *save);

void			put_prompt(char *prompt);

char			*remove_line_continuation(char *line);

void			welcome(t_line *line);

/*
** Termcaps
*/
void			go_home(t_line *line);
void			go_end(t_line *line);
void			left_arrow(t_line *line);
void			right_arrow(t_line *line);

void			next_word(t_line *line);
void			prev_word(t_line *line);

int				ft_pchar(int nb);
void			delete_down(void);
void			put_prompt(char *prompt);

void			up_arrow(t_line *line);
void			down_arrow(t_line *line);

void			create_hist(t_hist **begin, char **env);
void			save_history(int index, char *buff, 
							t_hist **curr, char **env);

void			deal_exit(t_line *line);
void			deal_cancel(t_line *line);
void			ft_clear(t_line *line);

void			del_lines(t_line *line);
void			deal_dleft(t_line *line);
void			del_right(t_line *line);

void			get_typing(t_line *line, int nb_read);
void			term_restore(struct termios save);
void			define_new_term(struct termios *save);

void			select_left(t_line *line);
void			select_right(t_line *line);
void			ft_copy(t_line *line);
void			ft_paste(t_line *line);
void			ft_cut(t_line *line);

/*
** Completion
*/
int				put_complet(char *str, t_tree *tern, char *tget, int *put,
		t_line *line, int *nb_ret);
void			get_complet(t_line *line);
void			set_complet(t_line *line);

void			feed_tree(char *str, unsigned char type,
		t_tree **tern, int lvl);
t_tree			*create_bin_tree(char **env);
t_tree			*create_file_tree(char *path);

void			set_psblty(t_tree *tern);
void			*free_tree(t_tree *tern);

void			reset_put(t_tree *tern);
void			deal_reset(t_tree *tree1, t_tree *tree2, t_tree *tree3);

t_line			*get_struct(void);
void			del_all_state(t_line *line);

/*
** globing
*/

t_slst			*deal_globing(char *str, t_tree *tree);

#endif
