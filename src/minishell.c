/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 00:01:41 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/06 22:05:58 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main_tools.h"
#include "token.h"

int		cmp_strpart(char *src, char *str, int *beg)
{
	int i;

	i = 0;
	while (src[i] && src[i] == str[*beg] && src[i] != '=')
	{
		i++;
		*beg += 1;
	}
	if (src[i] == '=')
		if (!str[*beg] || !ft_isalnum(str[*beg]))
			return (i);
	return (0);
}

char	*test_var(char **env, char *cmd)
{
	int		beg;
	int		end;
	int		to_cp;
	int		i;
	char	*ret;

	beg = 0;
	while (cmd[beg] != '$')
		beg++;
	beg++;
	i = 0;
	while (env[i])
	{
		end = beg;
		if ((to_cp = cmp_strpart(env[i], cmd, &end)))
		{
			ret = ft_strnew(to_cp + 2);
			ret[0] = '$';
			ft_strncpy(ret + 1, env[i], to_cp);
			ret[to_cp + 1] = '\0';
			return (ret);
		}
		i++;
	}
	return (NULL);
}

int		get_var(char **env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*var;
	char	*rep;

	i = -1;
	if (!env)
		return (0);
	while (cmd[++i])
		if (ft_occuc(cmd[i], '$'))
		{
			if (!(tmp = test_var(env, cmd[i])))
			{
				ft_putend(ft_strstr(cmd[i], "$"), " : Undefined variable.\n");
				return (0);
			}
			else
			{
				var = ft_strdup(cmd[i]);
				free(cmd[i]);
				cmd[i] = replace_str(var, tmp, (rep = get_env(env, &tmp[1])));
				free(tmp);
			}
		}
		else if (cmd[i][0] == '~')
		{
			tmp = get_env(env, "HOME");
			free(cmd[i]);
			cmd[i] = ft_strdup(tmp);
			free(tmp);
		}
	return (1);
}

void		deal_prompt(t_line *line)
{
	free(line->prompt);
	if (*(line->e_cmpl) & QUOTE)
		line->prompt = ft_strdup("quote> ");
	else if (*(line->e_cmpl) & BQUOTE)
		line->prompt = *(line->e_cmpl) & DQUOTE ? ft_strdup("dquote bquote> ") : ft_strdup("bquote> ");
	else if (*(line->e_cmpl) & DQUOTE && !(*(line->e_cmpl) & BQUOTE))
		line->prompt = ft_strdup("dquote> ");
	else
		line->prompt = ft_strdup("$> ");
	line->lprompt = ft_strlen(line->prompt);
}

void	reset_line(t_line *line)
{
	ft_bzero(line->curr->buff, 8193);
	ft_bzero(line->curr->buff_tmp, 8194);
	line->len = 0;
	line->index = 0;
}

int		main(__attribute((unused)) int ac, __attribute((unused)) char **av, char **ep)
{
	t_line	*line;
	t_token	*tokens;
	char	**env;

	env = collect_env(ep);
	line = get_struct();
	init_line(env, line);
	welcome(line);
	while (1)
	{
		put_prompt(line->prompt);
		check_path(line, env);
		deal_typing(line);
		write(1, "\n", 1);
		deal_prompt(line);
		if (*(line->e_cmpl) & QUOTE || *(line->e_cmpl) & DQUOTE || *(line->e_cmpl) & BQUOTE)
		{
			line->curr->next = ft_memalloc(sizeof(t_buff));
			line->curr->next->prev = line->curr;
			line->curr = line->curr->next;
			line->index = 0;
			line->len = 0;
			continue ;
		}
		if (line->curr->buff[0] && line->tmp[0] != -1 && line->curr->buff[0] != 10)
		{
			ft_putstr("line : ");
			ft_putendl(line->curr->buff);
			*(line->e_cmpl) &= ~COMPLETION;
			save_history(line->index, line->curr->buff, line->curr->buff_tmp, &(line->hist), env);
			ft_strcpy(line->curr->buff + line->len, "\n");
			tokens = get_tokens(line->curr->buff);
			for (t_token *ptr = tokens; ptr; ptr = ptr->next) {
				printf("------------------------------\n"
						"type:%d spec:%ld head:%ld tail:%ld quoted:%c\n",
						ptr->type, ptr->spec, ptr->head, ptr->tail, ptr->quoted);
				write(1, "command: \"", 10);
				write(1, line->curr->buff + ptr->head, ptr->tail - ptr->head);
				write(1, "\"\n", 2);
			}
			get_commands(tokens);
			reset_line(line);
		}
	}
	return (0);
}
