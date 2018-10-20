/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/20 19:07:45 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <term.h>
# include <dirent.h>

typedef struct			s_history
{
	char				*content;
	char				*tmp;
	size_t				c_size;
	struct s_history	*begin;
	struct s_history	*prev;
	struct s_history	*next;
}						t_hist;

typedef struct		s_tree
{
	int				value;
	int				max_len;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
}					t_tree;

char	**parsing(char *cmd);

void	deal_cmd(char **cmd, char ***env, struct termios *save);

char	*get_line(int fd);
char	*replace_str(char *path, char *src, char *replace);
void	free_tab(char ***tabl);
int		get_tab_len(char **tabl);
char	**ft_ralloc(char ***env, int len);

void	ft_setenv(char ***env, char *new, int len);
char	*get_env(char **env, char *to_get);
void	ft_unsetenv(char ***env, char **unset);
char	**collect_env(char **ep);

void	ft_cd(char ***env, char **cmd);

int		ft_exec(char **env, char **cmd, struct termios *save);

/* termcaps */

int		ft_pchar(int nb);
void	term_restore(struct termios save);
void	define_new_term(struct termios *save);
int		go_home(int index);
int		go_end(int index, int len);
void	left_arrow(int *index);
void	right_arrow(int *index, int i);
int		up_arrow(int *index, char *buff, char *buff_tmp, t_hist **curr);
int		down_arrow(int *index, char *buff, char *buff_tmp, t_hist **curr);
void	ft_exit2(struct termios save, t_hist **begin);
int		ft_cancel(int index, int i, char *buff_tmp, t_hist **curr);
void	del_lines(int index, int len, int nb_col);
int		del_left(int *index, char *buff, char *buff_tmp, t_hist *curr);
void	del_right(int index, int *i, char *buff);
void	ft_clear(char *buff, char *prompt);
void	next_word(int *index, int len, char *buff);
void	prev_word(int *index, int len, char *buff);
int		get_typing(int *index, char *buff, char *tmp, int nb_read);
void	deal_commande(int index, char *buff, char *buff_tmp, t_hist **curr);
void	create_hist(t_hist **begin);

t_tree	*create_file_tree(void);
void	put_complet(char *str, t_tree *tern);
t_tree	*create_tree(char **env);

#endif
