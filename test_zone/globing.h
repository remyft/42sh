/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:28:01 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/14 23:38:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# define IS_SLASH 1 << 0
# define IS_STAR 1 << 1
# define IS_REC 1 << 2
# define IS_MARK 1 << 3

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

typedef struct			s_strlst
{
	char				*str;
	struct s_strlst		*prev;
	struct s_strlst		*next;
}						t_slst;

void					get_new_mln(t_tree *tree, char *str, t_slist **glob,
		t_stint sti);
void					get_glob(t_tree *tree, char *tget, t_slist **glob,
		t_stint sti);
int						glob_brack(t_tree *tree, char *tget, t_slist **glob,
		t_stint sti);
void					glob_star(t_tree *tree, char **tget, t_slist **glob,
		t_stint *sti);
void					glob_slash(t_tree *tree, char **tget, t_slist **glob,
		t_stint *sti);

int						deal_star(char **src, char **targ);
int						deal_bracket(char **src, char **targ);
int						check_mln(char *src, char *targ);

#endif
