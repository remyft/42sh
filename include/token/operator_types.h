/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:24:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/10 23:00:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_TYPES_H
# define OPERATOR_TYPES_H

/*
** Identifiers for token OPERATOR
*/

enum
{
	OR_IF_VALUE = 1,
	PIPE_VALUE,
	PIPE_AND_VALUE,
	NOT_VALUE,
	AND_IF_VALUE,
	BACKGRND_VALUE,
	SEMI_VALUE,
	DSEMI_VALUE,
	LESS_VALUE,
	LESSAND_VALUE = 10,
	LESS_GREAT_VALUE,
	GREAT_VALUE,
	GREAT_PIPE_VALUE,
	AND_GREAT_VALUE,
	GREAT_AND_VALUE,
	DGREAT_VALUE,
	AND_DGREAT_VALUE,
	DGREAT_AND_VALUE,
	DLESS_VALUE,
	TLESS_VALUE = 20,
};

# define OR_IF				"||"
# define PIPE				"|"
# define PIPE_AND			"|&"
# define NOT				"!"
# define AND_IF				"&&"
# define BACKGRND			"&"
# define SEMI				";"
# define DSEMI				";;"
# define LESS				"<"
# define LESS_AND			"<&"
# define LESS_GREAT			"<>"
# define GREAT				">"
# define GREAT_PIPE			">|"
# define AND_GREAT			"&>"
# define GREAT_AND			">&"
# define DGREAT				">>"
# define AND_DGREAT			"&>>"
# define DGREAT_AND			">>&"
# define DLESS				"<<"
# define TLESS				"<<<"

# define OP_OR_IF			{ OR_IF,      OR_IF_VALUE }
# define OP_PIPE			{ PIPE,       PIPE_VALUE }
# define OP_PIPE_AND		{ PIPE_AND,   PIPE_AND_VALUE }
# define OP_NOT				{ NOT,        NOT_VALUE }
# define OP_AND_IF			{ AND_IF,     AND_IF_VALUE }
# define OP_BACKGRND		{ BACKGRND,   BACKGRND_VALUE }
# define OP_SEMI			{ SEMI,       SEMI_VALUE }
# define OP_DSEMI			{ DSEMI,      DSEMI_VALUE }
# define OP_LESS			{ LESS,       LESS_VALUE }
# define OP_LESSAND			{ LESS_AND,   LESSAND_VALUE }
# define OP_LESS_GREAT		{ LESS_GREAT, LESS_GREAT_VALUE }
# define OP_GREAT			{ GREAT,      GREAT_VALUE }
# define OP_GREAT_PIPE		{ GREAT_PIPE, GREAT_PIPE_VALUE }
# define OP_AND_GREAT		{ AND_GREAT,  AND_GREAT_VALUE }
# define OP_GREAT_AND		{ GREAT_AND,  GREAT_AND_VALUE }
# define OP_DGREAT			{ DGREAT,     DGREAT_VALUE }
# define OP_AND_DGREAT		{ AND_DGREAT, AND_DGREAT_VALUE }
# define OP_DGREAT_AND		{ DGREAT_AND, DGREAT_AND_VALUE }
# define OP_DLESS			{ DLESS,      DLESS_VALUE }
# define OP_TLESS			{ TLESS,      TLESS_VALUE }

#endif
