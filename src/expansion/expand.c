/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 20:18:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/24 03:17:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"
#include "token.h"
#include "expansion_types.h"

// static char		*ft_getenv(const char *name, char **env)
// {
// 	size_t		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (ft_strcmp(env[i], name) == '=')
// 			return (env[i] + ft_strlen(name));
// 		i++;
// 	}
// 	return (NULL);
// }

// static int			get_expansion_type(int c)
// {
// 	static t_type	type[] = {
// 		OP_EXP_BRACE, OP_EXP_TILDE, OP_EXP_DOLLAR, OP_EXP_PARENT, OP_EXP_SUBS,
// 	};
// 	size_t				i;

// 	i = 0;
// 	while (i < sizeof(type) / sizeof(*type))
// 	{
// 		if (type[i].c == c)
// 			return (type[i].value);
// 		i++;
// 	}
// 	return (EXP_NONE);
// }

// static t_expansion	*new_expansion(int c, size_t head, t_expansion *next)
// {
// 	t_expansion		*ret;

// 	if (!(ret = ft_memalloc(sizeof(*ret))))
// 		return (NULLEXPANSION);
// 	ret->type = get_expansion_type(c);
// 	ret->head = head;
// 	ret->tail = head;
// 	ret->next = next;
// 	return (ret);
// }

static int		exp_strlen(const char *str)
{
	int			i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

static char		*exp_strjoinfree(char *s1, char *s2, int tofree)
{
	char		*ret;

	if (!(ret = ft_memalloc(exp_strlen(s1) + exp_strlen(s2) + 1)))
		return (NULL);
	if (s1)
		ft_strcpy(ret, s1);
	if (s2)
		ft_strcat(ret, s2);
	if ((tofree == 1 || tofree == 3) && s1)
		free(s1);
	if ((tofree == 2 || tofree == 3) && s2)
		free(s2);
	return (ret);
}

static int		exp_strncmp(const char *s1, const char *s2, size_t n)
{
	char		*p1;
	char		*p2;

	p1 = (char *)s1;
	p2 = (char *)s2;
	while (*p1 && *p2 && n--)
		if (*p1++ != *p2++)
			break ;
	return (*p1 - *p2);
}

static char		*getnenv(const char *name, size_t len, char **env)
{
	size_t		i;

	i = 0;
	while (env[i])
	{
		if (exp_strncmp(env[i], name, len) == '=')
			return (&env[i][len + 1]);
	}
	return (NULL);
}

static int		dollar_special(int c)
{
	return ((c == '@')
		|| (c == '*')
		|| (c == '#')
		|| (c == '?')
		|| (c == '-')
		|| (c == '$')
		|| (c == '!'));
}

static int		dollar_valid_name(int c)
{
	return ((c == '_') || ft_isalnum(c));
}

static int		expand_backslash(size_t *i)
{
	*i = *i + 1;
	return (EXP_NONE);
}

static int		expand_dollar(const char *buff, size_t *i, t_token *token, char **str, t_s_env *e)
{
	(*i)++;
	if (*i == token->tail)
		return (ERR_NONE);
	if (ft_isdigit(buff[*i]))
	{
		int	j = ft_atoi(buff + *i);

		if (j < e->ac)
		{
			if (!(*str = exp_strjoinfree(*str, "\"", 1)))
				return (ERR_MALLOC);
			if (!(*str = exp_strjoinfree(*str, e->av[j], 1)))
				return (ERR_MALLOC);
			if (!(*str = exp_strjoinfree(*str, "\"", 1)))
				return (ERR_MALLOC);
		}
		while (ft_isdigit(buff[*i + 1]))
			(*i)++;
	}
	else if (dollar_special(buff[*i]))
	{
		if (buff[*i] == '@')
		{
			size_t	j = 1;
			while (e->av[j])
			{
				if (!(*str = exp_strjoinfree(*str, "\"", 1)))
					return (ERR_MALLOC);
				if (!(*str = exp_strjoinfree(*str, e->av[j], 1)))
					return (ERR_MALLOC);
				if (!(*str = exp_strjoinfree(*str, "\"", 1)))
					return (ERR_MALLOC);
				if (e->av[j + 1] && !(*str = exp_strjoinfree(*str, " ", 1)))
					return (ERR_MALLOC);
				j++;
			}
		}
		else if (buff[*i] == '*')
		{
			size_t	j = 1;
			if (!(*str = exp_strjoinfree(*str, "\"", 1)))
				return (ERR_MALLOC);
			while (e->av[j])
			{
				if (!(*str = exp_strjoinfree(*str, e->av[j], 1)))
					return (ERR_MALLOC);
				if (e->av[j + 1] && !(*str = exp_strjoinfree(*str, " ", 1)))
					return (ERR_MALLOC);
				j++;
			}
			if (!(*str = exp_strjoinfree(*str, "\"", 1)))
				return (ERR_MALLOC);
		}
		else if (buff[*i] == '#')
		{
			if (!(*str = exp_strjoinfree(*str, ft_itoa(e->ac - 1), 3)))
				return (ERR_MALLOC);
		}
		else if (buff[*i] == '?')
		{
			if (!(*str = exp_strjoinfree(*str, ft_itoa(e->ret), 3)))
				return (ERR_MALLOC);
		}
		else if (buff[*i] == '-')
		{
			/* 21sh options ... */
		}
		else if (buff[*i] == '$')
		{
			if (!(*str = exp_strjoinfree(*str, ft_itoa(e->pid), 3)))
				return (ERR_MALLOC);
		}
		else if (buff[*i] == '!')
		{
			/* job control pid list */
		}
	}
	else if (buff[*i] == '{')
	{
		(*i)++;
	}
	else if (buff[*i] == '(')
	{
		(*i)++;
	}
	else if (ft_isalpha(buff[*i]) || buff[*i] == '_')
	{
		size_t	j = *i;

		while (j < token->tail && dollar_valid_name(buff[j]))
			j++;
		if (!(*str = exp_strjoinfree(*str, getnenv(buff + *i, j, e->env), 1)))
			return (ERR_MALLOC);
		*i = j - 1;
	}
	return (ERR_NONE);
}

static int		expand_argument(const char *buff, t_argument *arg, t_s_env *e)
{
	char		*ifs;
	t_token		*token;
	size_t		i;
	int			error;

	if (!arg)
		return (ERR_NONE);
	ifs = SEPARATORS;
	token = arg->token;
	i = token->head;
	error = ERR_NONE;
	while (i < token->tail)
	{
		if (buff[i] == '\\')
			error = expand_backslash(&i);
		else if (buff[i] == '$')
			error = expand_dollar(buff, &i, token, &arg->result, e);
		// else if (buff[i] == '`')
		// 	error = expand_backquote();
		// else if (buff[i] == '"')
		// 	error = expand_dquote();
		// else if (buff[i] == '\'')
		// 	error = expand_squote();
		// else if (buff[i] == '~')
		// 	error = expand_tilde();
		// else if (buff[i] == '*' || buff[i] == '[' || buff[i] == '?')
		// 	error = expand_glob();
		if (error != ERR_NONE)
			return (error);
		i++;
	}
	if (arg->result)
		ft_putendl(arg->result);
	return (expand_argument(buff, arg->next, e));
}

static int		check_type(const char *buff, void *cmd, t_s_env *e)
{
	int			error;

	error = ERR_NONE;
	if (!cmd)
		return (ERR_NONE);
	if ((error = expand_argument(buff, ((t_command *)cmd)->args, e)) != ERR_NONE)
		return (error);
	if (*(int *)cmd == IS_A_PIPE)
		error = check_type(buff, ((t_pipeline *)cmd)->right, e);
	else if (((t_command *)cmd)->redir)
		error = expand_argument(buff, ((t_command *)cmd)->redir->arg, e);
	return (error);
}

int				expand(const char *buff, t_m_list *list, t_s_env *e)
{
	int			error;

	if (!list)
		return (ERR_NONE);
	if (list->aolist)
		if ((error = check_type(buff, list->aolist->cmd, e)) != ERR_NONE)
			return (expand_error(error, e));
	return (expand(buff, list->next, e));
}
