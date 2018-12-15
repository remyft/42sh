/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:59:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/15 18:25:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"

/*
** Structure for AND_OR list elements
*/
# define NULLNODE	(t_node *)0
typedef struct	s_node
{
	t_token			*token;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

/*
** Structure for AND-OR list ( '&&' and '||' )
*/
# define IS_AOLIST(x)	((x == OR_IF) || (x == AND_IF))
# define NULLAOLIST		(t_ao_list *)0
typedef struct	s_and_or_list
{
	int						mode;
	t_node					*node;
	struct s_and_or_list	*next;
}				t_ao_list;

/*
** Structure for list ( ';' and '&' )
*/
# define IS_LIST(x)	((x == SEMI) || (x == BACKGRND))
# define NULLLIST	(t_m_list *)0
typedef struct	s_main_list
{
	int					mode;
	t_ao_list			*aolist;
	struct s_main_list	*next;
}				t_m_list;

t_m_list		*parse(const char *buff, t_token *token);
t_m_list		*parse_error(const char *buff, t_token *token, t_m_list *list);
void			free_m_list(t_m_list **list);

void			debug_parser(const char *buff, t_m_list *list);
#endif
