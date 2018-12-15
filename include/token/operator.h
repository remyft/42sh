/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/14 17:27:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEARTOR_H
# define OPEARTOR_H

/*
** Specificities for token OPERATOR
*/

enum
{
	OR_IF,
	PIPE,
	PIPE_AND,
	NOT,
	AND_IF,
	BACKGRND,
	SEMI,
	DSEMI,
	LESS,
	LESSAND,
	LESS_GREAT,
	GREAT,
	GREAT_PIPE,
	AND_GREAT,
	GREAT_AND,
	DGREAT,
	AND_DGREAT,
	DGREAT_AND,
	DLESS,
	TLESS,
};

# define OP_OR_IF				{ "||",  OR_IF }
# define OP_PIPE				{ "|",   PIPE }
# define OP_PIPE_AND			{ "|&",  PIPE_AND }
# define OP_NOT					{ "!",   NOT }
# define OP_AND_IF				{ "&&",  AND_IF }
# define OP_BACKGRND			{ "&",   BACKGRND }
# define OP_SEMI				{ ";",   SEMI }
# define OP_DSEMI				{ ";;",  DSEMI }
# define OP_LESS				{ "<",   LESS }
# define OP_LESSAND				{ "<&",  LESSAND }
# define OP_LESS_GREAT			{ "<>",  LESS_GREAT }
# define OP_GREAT				{ ">",   GREAT }
# define OP_GREAT_PIPE			{ ">|",  GREAT_PIPE }
# define OP_AND_GREAT			{ "&>",  AND_GREAT }
# define OP_GREAT_AND			{ ">&",  GREAT_AND }
# define OP_DGREAT				{ ">>",  DGREAT }
# define OP_AND_DGREAT			{ "&>>", AND_DGREAT }
# define OP_DGREAT_AND			{ ">>&", DGREAT_AND }
# define OP_DLESS				{ "<<",  DLESS }
# define OP_TLESS				{ "<<<", TLESS }

#endif
