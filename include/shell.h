/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:02:40 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include "struct.h"
# include "shell_env.h"

# define RC_NAME		".21shrc"
# define CANCEL			"\x3"
# define EXIT			"\x4"
# define GET_COMPLETION	"\x9"
# define CLEAR			"\xB"
# define NEXT_WORD		"\x1B\x1B\x5B\x43"
# define PREV_WORD		"\x1B\x1B\x5B\x44"
# define DELETE_LEFT	"\x7F"
# define DELETE_RIGHT	"\x1B\x5B\x33\x7E"
# define MOVE_UP		"\x1B\x1B\x5B\x41"
# define MOVE_DOWN		"\x1B\x1B\x5B\x42"
# define UP_ARROW		"\x1B\x5B\x41"
# define DOWN_ARROW		"\x1B\x5B\x42"
# define RIGHT_ARROW	"\x1B\x5B\x43"
# define LEFT_ARROW		"\x1B\x5B\x44"
# define GO_END			"\x1B\x5B\x46"
# define GO_HOME		"\x1B\x5B\x48"
# define COPY			"\xC3\xA7"
# define PASTE			"\xE2\x88\x9A"
# define CUT			"\xE2\x89\x88"
# define SELECT_LEFT	"\x1B\x5B\x31\x3B\x32\x44"
# define SELECT_RIGHT	"\x1B\x5B\x31\x3B\x32\x43"
# define SELECT_UP		"\x1B\x5B\x31\x3B\x32\x41"
# define SELECT_DOWN	"\x1B\x5B\x31\x3B\x32\x42"

char			*get_line(int fd);
void			free_tab(char ***tabl);
int				get_tab_len(char **tabl);
char			**ft_ralloc(char ***env, int len);

void			ft_setenv(char ***env, char *new, int len);
char			*get_env(char **env, char *to_get);
char			**collect_env(char **ep);

void			launch_rc(t_s_env *e, int fd, char *path);
void			get_rc(t_s_env *e);

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
** Completion
*/
void			feed_tree(char *str, unsigned char type,
		t_tree **tern, int lvl);
t_tree			*create_bin_tree(char **env);
t_tree			*create_env_tree(char **env);
t_tree			*create_file_tree(char *path, char *beg, t_tree *tern);

void			set_psblty(t_tree *tern, int set);
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
void			reset_hist(t_line *line);

void			put_prompt(char *prompt);

char			*remove_line_continuation(char *line);

void			free_buff(t_line *line);
t_line			*get_struct(void);
void			free_struct(t_line *line);
void			del_all_state(t_line *line);

#endif
