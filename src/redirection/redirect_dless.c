/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:21:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/17 19:47:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "shell_env.h"

/*
** Anime must watch (@ touche speciale agrum)
**  - Made in Abyss (TOP 1 gold trop beau, la perfection apres Miyazaki) @
**  - Konosuba (trop drole xD) @
**  - re zero (poignant, mais evite de regarde le dernier ep) @
**  - Erased (deprimant)
**  - Mob psycho 100 (TROP marrant)
**  - One Piece (m'enfin Gillou!!!)
** Les mangas! Et oui Gillou!
**  - Berzerk (gillou il faut) @
**  - Gosu (TOP 1 trop marrant) @
** Pour toi Gillou
**  - Nichijou (wtf)
*/

int				redirect_dless(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 0;
	(*redir)->fdarg = 0;
	(void)e;
	return (0);
}
