/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:42:37 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/12 09:58:26 by rfontain         ###   ########.fr       */
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
	WT_SPACE = 1 << 4,
	WT_HDOC = 1 << 5,
	HDOC = 1 << 6,
	NSTATE = 1 << 7
}					t_st;

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

typedef struct		s_hdlist
{
	int				head;
	int				tail;
	struct s_hdlist	*next;
	struct s_hdlist	*prev;
}					t_hdlist;

typedef struct		s_line
{
	t_buff			*curr;
	t_buff			*beg_buff;
	char			tmp[10];
	char			*copy;
	char			*prompt;
	char			*path;
	char			*term;
	int				lprompt;
	int				index;
	int				slct_beg;
	int				slct_end;
	int				len;
	int				nb_col;
	int				nb_line;
	t_hdlist		*hdoc;
	t_hist			*hist;
	t_st			*e_cmpl;
	t_tree			*tree[3];
	struct termios	save;
	char			**env;
}					t_line;

t_line	*get_struct(void);

#endif
