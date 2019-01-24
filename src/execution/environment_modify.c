/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_modify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:16:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:45:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_lib.h"
#include "parser.h"

char			**modify_environ(t_argument *var, t_argument *end, char **env)
{
	char		**ptr;
	char		*equal;
	size_t		i;

	while (var != end)
	{
		i = 0;
		while (var->cmd[i])
		{
			equal = ft_strchr(var->cmd[i], '=');
			*equal = '\0';
			if ((ptr = exp_getnenvaddr(var->cmd[i], env)))
				free(*ptr);
			else if (!(ptr = exp_newenv(&env)))
				return (NULL);
			*equal = '=';
			*ptr = var->cmd[i];
			var->cmd[i] = NULL;
			i++;
		}
		var = var->next;
	}
	return (env);
}
