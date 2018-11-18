/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:20:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/11/18 19:21:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "token.h"

static t_token	*new_token(char rights, char *line)
{
	t_token		*ret;

	ret = (t_token *)malloc(sizeof(*ret));
	if (ret == NULL)
		return (NULL);
	ret->rights = rights;
	ret->line = line;
	ret->head = (t_cmd *)0;
	ret->next = (t_token *)0;
	return (ret);
}

static t_token	*fill_token(t_token *ptr, const char *buff, t_var *var, \
							char rights, unsigned int len)
{
	if (ptr == (t_token *)0)
		ptr = new_token(var->rights, ft_strsub(buff, var->j, var->i - var->j));
	else
	{
		ptr->next = new_token(var->rights, ft_strsub(buff, var->j, var->i - var->j));
		ptr = ptr->next;
	}
	var->i += len;
	var->j = var->i + 1;
	var->rights = rights;
	return (ptr);
}

static t_token	*check_tokens(const char *buff, t_var *var, t_token *ptr)
{
	if (!var->quoted && (buff[var->i] == '"' || buff[var->i] == '\''))
		var->quoted = buff[var->i];
	else if (var->quoted == buff[var->i])
		var->quoted = 0;
	if (var->quoted)
		return (ptr);
	if (buff[var->i] == ';')
		ptr = fill_token(ptr, buff, var, EXECUTE, 0);
	else if (ft_strncmp(buff + var->i, "&&", 2) == 0)
		ptr = fill_token(ptr, buff, var, EXECUTE_IF_OK, 1);
	else if (ft_strncmp(buff + var->i, "||", 2) == 0)
		ptr = fill_token(ptr, buff, var, EXECUTE_IF_NOT, 1);
	return (ptr);
}

t_token			*get_tokens(char *buff)
{
	t_var		var;
    t_token		*ret;
	t_token		*ptr;

	ft_memset(&var, 0, sizeof(var));
	var.rights = EXECUTE;
	ret = (t_token *)0;
	ptr = ret;
	while (buff[var.i] && buff[var.i] != '#')
	{
		if (buff[var.i] != '\\')
		{
			ptr = check_tokens(buff, &var, ptr);
			if (!ret)
				ret = ptr;
			var.i++;
		}
		else if (var.quoted != '\'')
			var.i += 2;
		else if (buff[var.i + 1] == '\n')
			ft_strcpy(buff + var.i, buff + var.i + 2);
	}
	ptr = fill_token(ptr, buff, &var, EXECUTE, 0);
    return ((ret) ? ret : ptr);
}
