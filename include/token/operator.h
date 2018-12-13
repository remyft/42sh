/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/12 10:16:16 by gbourgeo         ###   ########.fr       */
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
# define LESS				{ "<",   8 }
# define LESSAND			{ "<&",  9 }
# define LESS_GREAT			{ "<>",  10 }
# define GREAT				{ ">",   11 }
# define GREAT_PIPE			{ ">|",  12 }
# define AND_GREAT			{ "&>",  13 }
# define GREAT_AND			{ ">&",  14 }
# define DGREAT				{ ">>",  15 }
# define AND_DGREAT			{ "&>>", 16 }
# define DGREAT_AND			{ ">>&", 17 }
# define DLESS				{ "<<",  18 }
# define TLESS				{ "<<<", 19 }

#endif
