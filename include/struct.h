/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:42:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/15 00:14:40 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <term.h>
# include <string.h>

typedef enum		e_state
{
	COMPLETION = 1 << 0,
	QUOTE = 1 << 1,
	DQUOTE = 1 << 2,
	BQUOTE = 1 << 3,
	WT_NHDOC = 1 << 4,
	WT_SPACE = 1 << 5,
	WT_HDOC = 1 << 6,
	UN_HDOC = 1 << 7,
	HDOC = 1 << 8,
	NSTATE = 1 << 9
}					t_st;

typedef struct		s_tree
{
	int				value;
	int				max_len;
	int				tput;
	int				npsb;
	int				len;
	unsigned char	type;
	struct s_tree	*left;
	struct s_tree	*right;
	struct s_tree	*tern_next;
	struct s_tree	*prev;
}					t_tree;

typedef struct		s_select
{
	t_tree				*mln;
	struct s_select		*next;
	struct s_select		*down;
}					t_slct;

typedef struct			s_history
{
	char				*content;
	char				*tmp;
	size_t				c_size;
	struct s_history	*begin;
	struct s_history	*prev;
	struct s_history	*next;
}						t_hist;

typedef struct		s_buff
{
	char			buff[8193];
	char			buff_tmp[8194];
	struct s_buff	*next;
	struct s_buff	*prev;
}					t_buff;

typedef struct		s_state
{
	int				state;
	size_t			head;
	size_t			tail;
	struct s_state	*next;

	char			*cmd;
	struct s_state	*prev;
}					t_state;

typedef struct		s_line
{
	t_buff			*curr;
	t_buff			*beg_buff;
	char			tmp[10];
	char			*copy;
	char			*prompt;
	char			*path;
	char			*term;
	size_t			lprompt;
	int				slct_beg;
	int				slct_end;
	size_t			index;
	size_t			len;
	size_t			nb_col;
	size_t			nb_line;
	t_state			*hdoc;
	t_hist			*hist;
	t_st			*e_cmpl;
	t_tree			*tree[3];
	struct termios	save;
	char			**env;
}					t_line;

typedef struct			s_str_list
{
	char				*str;
	t_tree				*mln;
	int					state;
	struct s_str_list	*next;
	struct s_str_list	*prev;
}						t_slist;

typedef struct			s_stint
{
	char				*str;
	int					nb;
}						t_stint;

typedef struct	s_fctn
{
	char		*key;
	void		(*f)(t_line*);
}				t_fctn;

typedef struct			s_strlst
{
	char				*str;
	struct s_strlst		*prev;
	struct s_strlst		*next;
}						t_slst;


t_line	*get_struct(void);

#endif
