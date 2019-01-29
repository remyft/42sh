/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/29 21:32:23 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_21SH_H
# define H_21SH_H

# include "libft.h"
# include "struct.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>

char			*get_line(int fd);
void			free_tab(char ***tabl);
int				get_tab_len(char **tabl);
char			**ft_ralloc(char ***env, int len);

void			ft_setenv(char ***env, char *new, int len);
char			*get_env(char **env, char *to_get);
char			**collect_env(char **ep);

void			put_prompt(char *prompt);

char			*remove_line_continuation(char *line);

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

void			deal_prompt(t_line *line);
void			reset_line(t_line *line);
void			free_buff(t_line *line);
char			*listnjoin(t_line *line);

/*
**	Select, copy, cut and paste
*/

void			select_left(t_line *line);
void			select_right(t_line *line);

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

int				put_complet(t_tree *tern, int *put, t_line *line, int *nb_ret);
void			get_complet(t_line *line);
void			set_complet(t_line *line, int set);

void			feed_tree(char *str, unsigned char type,
		t_tree **tern, int lvl);
t_tree			*create_bin_tree(char **env);
t_tree			*create_file_tree(char *path, t_tree *tern);

void			set_psblty(t_tree *tern);
void			*free_tree(t_tree *tern);
void			free_all_tree(t_line *line);

void			reset_put(t_tree *tern);
void			deal_reset(t_tree *tree1, t_tree *tree2, t_tree *tree3);

t_line			*get_struct(void);
void			del_all_state(t_line *line);

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
void			reset_buff(t_line *line);
void			reset_hist(t_line *line);

#endif
