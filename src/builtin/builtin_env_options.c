/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:25:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 20:04:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_env.h"

static int	env_options_loop(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	static t_opt	options[] = {
		ENV_OPTION_LESS, ENV_OPTION_I, ENV_OPTION_V, ENV_OPTION_P, ENV_OPTION_U,
	};
	size_t			nb;

	nb = 0;
	while (nb < sizeof(options) / sizeof(options[0]))
	{
		if (cmd[*i][*j] == options[nb].value)
			return (options[nb].handler(i, j, cmd, opt));
		nb++;
	}
	return (ERR_ILLEGAL_OPT);
}

int			builtin_env_options(size_t *i, size_t *j, char **cmd, t_e_opt *opt)
{
	int			error;

	*i = 1;
	while (cmd[*i] && cmd[*i][0] == '-')
	{
		if (!cmd[*i][1])
			opt->options |= BUILTIN_OPT_I;
		else if (!ft_strcmp(cmd[*i], "--"))
			return (ERR_OK);
		else
		{
			*j = 0;
			while (cmd[*i] && cmd[*i][++(*j)])
			{
				if ((error = env_options_loop(i, j, cmd, opt)) != ERR_OK)
					return (error);
				if (opt->options & BUILTIN_OPT_P
				|| opt->options & BUILTIN_OPT_U)
					break ;
			}
			*j = 0;
		}
		++(*i);
	}
	return (ERR_OK);
}
