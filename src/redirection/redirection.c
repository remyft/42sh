/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:59:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/09 17:48:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_less(t_redirection *redir)
{
	ft_putendl("redirect_less");
	(void)redir;
	return (0);
}

int				redirect_less_and(t_redirection *redir)
{
	ft_putendl("redirect_less_and");
	(void)redir;
	return (0);
}

int				redirect_less_great(t_redirection *redir)
{
	ft_putendl("redirect_less_great");
	(void)redir;
	return (0);
}

int				redirect_great(t_redirection *redir)
{
	ft_putendl("redirect_great");
	(void)redir;
	return (0);
}

int				redirect_great_pipe(t_redirection *redir)
{
	ft_putendl("redirect_great_pipe");
	(void)redir;
	return (0);
}

int				redirect_and_great(t_redirection *redir)
{
	ft_putendl("redirect_and_great");
	(void)redir;
	return (0);
}

int				redirect_great_and(t_redirection *redir)
{
	ft_putendl("redirect_great_and");
	(void)redir;
	return (0);
}

int				redirect_dgreat(t_redirection *redir)
{
	ft_putendl("redirect_dgreat");
	(void)redir;
	return (0);
}

int				redirect_and_dgreat(t_redirection *redir)
{
	ft_putendl("redirect_and_dgreat");
	(void)redir;
	return (0);
}

int				redirect_dgreat_and(t_redirection *redir)
{
	ft_putendl("redirect_dgreat_and");
	(void)redir;
	return (0);
}

int				redirect_dless(t_redirection *redir)
{
	ft_putendl("redirect_dless");
	(void)redir;
	return (0);
}

int				redirect_tless(t_redirection *redir)
{
	ft_putendl("redirect_tless");
	(void)redir;
	return (0);
}


static int		redir_error(const char *buff, t_redirection *redir, t_s_env *e)
{
	size_t		len;

	len = redir->token->tail - redir->token->head;
	ft_putstr_fd(e->progname, STDERR_FILENO);
	ft_putstr_fd(": Unknown redirection `", STDERR_FILENO);
	write(STDERR_FILENO, buff + redir->token->head, len);
	ft_putendl_fd("'", STDERR_FILENO);
	return (1);
}

static size_t	max(size_t a, t_token *token)
{
	if (token->tail - token->head > a)
		return (token->tail - token->head);
	return (a);
}

int				redirection(const char *buff, t_redirection *redir, t_s_env *e)
{
	static t_redir	redirect[] = {
		REDIR_LESS, REDIR_LESS_AND, REDIR_LESS_GREAT, REDIR_GREAT,
		REDIR_GREAT_PIPE, REDIR_AND_GREAT, REDIR_GREAT_AND, REDIR_DGREAT,
		REDIR_AND_DGREAT, REDIR_DGREAT_AND, REDIR_DLESS, REDIR_TLESS,
	};
	size_t			i;
	size_t			size;

	if (!redir)
		return (0);
	i = 0;
	while (i < sizeof(redirect) / sizeof(redirect[0]))
	{
		size = max(ft_strlen(redirect[i].value), redir->token);
		if (!ft_strncmp(redirect[i].value, buff + redir->token->head, size))
			return (redirect[i].handler(redir));
		i++;
	}
	return (redir_error(buff, redir, e));
}
