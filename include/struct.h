/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 02:42:37 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 11:31:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <term.h>
# include <string.h>

typedef enum		e_state
{
	COMPLETION = 1 << 0,
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

typedef struct		s_line
{
	char			buff[8193];
	char			buff_tmp[8194];
	char			tmp[10];
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
	t_hist			*curr;
	t_st			*e_cmpl;
	t_tree			*tree[3];
	struct termios	save;
}					t_line;

#endif
