/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:49:03 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/18 03:02:16 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
	int				tput;
	int				npsb;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
}					t_tree;

typedef enum		e_state
{
	COMPLETION = 1 << 0,
}					t_st;

typedef struct		s_line
{
	char			buff[8193];
	char			buff_tmp[8194];
	char			tmp[10];
	int				index;
	int				len;
	t_hist			*curr;
	t_st			*e_cmpl;
	t_tree			*tree[3];
	struct termios	save;
}					t_line;

typedef struct		s_fctn
{
	char			*key;
	void			(*f)(t_line*);
}					t_fctn;

typedef struct		s_select
{
	t_tree				*mln;
	struct s_select		*next;
	struct s_select		*down;
}					t_slct;

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

void	put_prompt(void);

/* termcaps */

int		ft_pchar(int nb);
void	term_restore(struct termios save);
void	define_new_term(struct termios *save);
void	go_home(t_line *line);
void	go_end(t_line *line);
void	left_arrow(t_line *line);
void	right_arrow(t_line *line);
void	up_arrow(t_line *line);
void	down_arrow(t_line *line);
void	ft_exit2(t_line *line);
void	deal_cancel(t_line *line);
void	del_lines(t_line *line);
void	deal_dleft(t_line *line);
void	del_right(t_line *line);
void	ft_clear(t_line *line);
void	next_word(t_line *line);
void	prev_word(t_line *line);
int		get_typing(int *index, char *buff, char *tmp, int nb_read, char *buff_tmp);
void	deal_commande(int index, char *buff, char *buff_tmp, t_hist **curr, char **env);
void	create_hist(t_hist **begin, char **env);
void	delete_down(void);

t_tree	*create_file_tree(char *path);
int		put_complet(char *str, t_tree *tern, char *tget, int *put);
t_tree	*create_tree(char **env);
void	*free_tree(t_tree *tern);
void	reset_put(t_tree *tern);
void	deal_reset(t_tree *tree1, t_tree *tree2, t_tree *tree3);
void	get_complet(t_line *line);
int		set_complet(t_tree **file, t_st *e_cmpl, char *tmp, char *buff, int *i, char *buff_tmp);

#endif
