/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:59:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/10 06:12:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "token.h"

# define NULLTREE	(t_command *)0
# define NULLNODE	(t_node *)0

typedef struct	s_node
{
	struct s_node	*left;
	t_token			*token;
	struct s_node	*right;
}				t_node;

typedef struct	s_command
{
	t_node				*node;
	struct s_command	*next;
}				t_command;

t_command			*parse(const char *buff, t_token *token);

#endif
