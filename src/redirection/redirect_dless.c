/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:21:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/27 23:10:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "redirection.h"
#include "struct.h"

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

static int		handle_here_doc(t_redirection **redir, t_s_env *e)
{
	static size_t	fnum = 0;
	int				mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	if (!((*redir)->file = ft_strjoinfree("/tmp/.21sh_tmpfile_",
											ft_itoa(fnum++), 2)))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	if (((*redir)->fdarg = open((*redir)->file, mode, 0600)) < 0)
		return (redirect_open_error((*redir)->file, e));
	write((*redir)->fdarg, (*redir)->heredoc->head, (*redir)->heredoc->len + 1);
	return (0);
}

int				redirect_dless(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 0;
	if (handle_here_doc(redir, e))
		return (1);
	if (((*redir)->fdarg = open((*redir)->file, O_RDONLY)) < 0)
		return (redirect_open_error((*redir)->file, e));
	return (0);
}
