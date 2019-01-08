/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:59:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/08 23:48:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_input(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				redirect_output1(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				redirect_output2(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				append_redirect_output(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				redirect_here_doc(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				duplicate_input(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				duplicate_output(t_redirection *redir)
{
	(void)redir;
	return (0);
}
int				redirect_read_write(t_redirection *redir)
{
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

int				redirection(const char *buff, t_redirection *redir, t_s_env *e)
{
	static t_redir	redirect[] = {
		REDIR_INPUT, REDIR_OUTPUT1, REDIR_OUTPUT2, REDIR_OUTPUT_APP,
		REDIR_HERE_DOC, DUPLICATE_INPUT, DUPLICATE_OUTPUT, REDIR_RD_WR,
	};
	size_t			i;

	if (!redir)
		return (0);
	i = 0;
	write(STDERR_FILENO, buff + redir->token->head, redir->token->tail - redir->token->head);
	while (i < sizeof(redirect) / sizeof(redirect[0]))
	{
		if (!ft_strcmp(redirect[i].value, buff + redir->token->head))
			return (redirect[i].handler(redir));
		i++;
	}
	return (redir_error(buff, redir, e));
}
