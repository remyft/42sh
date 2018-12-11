/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/11 07:25:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEARTOR_H
# define OPEARTOR_H

/*
** Specificities for token OPERATOR
*/

# define OR_IF				{ "||",  0 }
# define PIPE				{ "|",   1 }
# define PIPE_AND			{ "|&",  2 }
# define NOT				{ "!",   3 }
# define AND_IF				{ "&&",  4 }
# define BACKGRND			{ "&",   5 }
# define SEMI				{ ";",   6 }
# define DSEMI				{ ";;",  7 }
# define PAREN_LEFT			{ "(",   8 }
# define PAREN_RIGHT		{ ")",   9 }
# define LESS				{ "<",   10 }
# define LESSAND			{ "<&",  11 }
# define LESS_GREAT			{ "<>",  12 }
# define GREAT				{ ">",   13 }
# define GREAT_PIPE			{ ">|",  14 }
# define AND_GREAT			{ "&>",  15 }
# define GREAT_AND			{ ">&",  16 }
# define DGREAT				{ ">>",  17 }
# define AND_DGREAT			{ "&>>", 18 }
# define DGREAT_AND			{ ">>&", 19 }
# define DLESS				{ "<<",  20 }
# define TLESS				{ "<<<", 21 }

#endif
