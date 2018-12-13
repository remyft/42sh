/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 00:01:41 by rfontain          #+#    #+#             */
/*   Updated: 2018/12/13 19:42:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "main_tools.h"
#include "token.h"
#include "parser.h"

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
	else if (*(line->e_cmpl) & DQUOTE && *(line->e_cmpl) & ~BQUOTE)
		line->prompt = ft_strdup("dquote> ");
	else if (*(line->e_cmpl) & HDOC)
		line->prompt = ft_strdup("heredoc> ");
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

void	free_buff(t_line *line)
{
	while (line->curr->prev)
		line->curr = line->curr->prev;
	while (line->curr && line->curr->next)
	{
		if (line->curr->prev)
			free(line->curr->prev);
		line->curr = line->curr->next;
	}
	if (line->curr)
		free(line->curr);
	line->curr = ft_memalloc(sizeof(t_buff));
	line->beg_buff = line->curr;
	line->index = 0;
	line->len = 0;
}

char	*listnjoin(t_line *line)
{
	char	*str;
	t_buff	*begin;

	while (line->curr->prev)
		line->curr = line->curr->prev;
	begin = line->curr;
	str = ft_strdup(line->curr->buff);
	if (line->curr->next)
		str = ft_strjoinfree(str, "\n", 1);
	line->curr = line->curr->next;
	while (line->curr && line->curr->next)
	{
		str = ft_strjoinfree(str, line->curr->buff, 1);
		str = ft_strjoinfree(str, "\n", 1);
		line->curr = line->curr->next;
	}
	if (line->curr)
		str = ft_strjoinfree(str, line->curr->buff, 1);
	line->curr = begin;
	return (str);
}

int			ft_strhtcmp(char *str1, char *str2, int head, int tail)
{
	if (((int)ft_strlen(str1)) != tail - head)
		return (-1);
	return (ft_strncmp(str1, &str2[head], tail - head));
}

static int	deal_hdoc(t_line *line)
{
	t_state *tmp;

	if (!line->curr->prev)
		return (0);
	while (line->hdoc && line->hdoc->prev)
		line->hdoc = line->hdoc->prev;
	tmp = ft_memalloc(sizeof(t_state));
	tmp->head = 0;
	tmp->tail = ft_strlen(line->curr->buff);
	tmp->cmd = expand_word(line->curr->buff, (t_token*)tmp);
	if (tmp->cmd && line->hdoc && line->hdoc->cmd && ft_strcmp(tmp->cmd, line->hdoc->cmd) == 0)
	{
		if (line->hdoc->next)
		{
			line->hdoc = line->hdoc->next;
			free(line->hdoc->prev->cmd);
			free(line->hdoc->prev);
			line->hdoc->prev = NULL;
			free(tmp->cmd);
			free(tmp);
			return (1);
		}
		else
		{
			free(line->hdoc->cmd);
			free(line->hdoc);
			line->hdoc = NULL;
			*(line->e_cmpl) &= ~HDOC;
			deal_prompt(line);
			free(tmp->cmd);
			free(tmp);
			return (1);
		}
	}
	free(tmp->cmd);
	free(tmp);
	return (0);
}

int		deal_continue(t_line *line)
{
	if (*(line->e_cmpl) & QUOTE || *(line->e_cmpl) & DQUOTE
			|| *(line->e_cmpl) & BQUOTE || *(line->e_cmpl) & HDOC || *(line->e_cmpl) & WT_HDOC)
	{
		line->curr->next = ft_memalloc(sizeof(t_buff));
		line->curr->next->prev = line->curr;
		line->curr = line->curr->next;
		line->index = 0;
		line->len = 0;
		return (1);
	}
	return (0);
}

void		change_state(t_line *line, int state)
{
	if (*(line->e_cmpl) & state)
		*(line->e_cmpl) &= ~state;
	else
		*(line->e_cmpl) |= state;
	return ;
}

void		deal_state(t_line *line, char c)
{
	if (c == '\'')
	{
		if (!(*(line->e_cmpl) & DQUOTE) && !(*(line->e_cmpl) & BQUOTE)
				&& !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, QUOTE));
	}
	else if (c == '"')
	{
		if (!(*(line->e_cmpl) & QUOTE) && !(*(line->e_cmpl) & BQUOTE)
				&& !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, DQUOTE));
	}
	else if (c == '`')
	{
		if (!(*(line->e_cmpl) & QUOTE) && !(*(line->e_cmpl) & NSTATE))
			return (change_state(line, BQUOTE));
	}
}

int		check_hdoc(t_line *line)
{
	int		i;
	int		state;
	t_buff	*buff;

	i = 0;
	state = 0;
	buff = line->curr;
	while (line->curr->buff[i])
	{
		if (!(state & NSTATE))
			deal_state(line, line->curr->buff[i]);
		if (!line->curr->prev && !(state & UN_HDOC))
		{
			if (line->curr->buff[i] == '\\' && !(state & NSTATE))
				state |= NSTATE;
			else if (state & NSTATE)
			{
				state &= ~NSTATE;
				if (line->curr->buff[i] == '<')
					i++;
			}
			if (line->curr->buff[i] == '<' && !(state & WT_NHDOC) && !(state & NSTATE))
				state |= WT_NHDOC;
			else if (line->curr->buff[i] == '<' && state & WT_NHDOC)
			{
				if (state & WT_SPACE)
					state |= UN_HDOC;
				else
					state |= WT_SPACE;
			}
			else if (line->curr->buff[i] != ' ' && state & WT_SPACE)
			{
				if (!line->hdoc)
					line->hdoc = ft_memalloc(sizeof(*line->hdoc));
				else
				{
					line->hdoc->next = ft_memalloc(sizeof(*line->hdoc));
					line->hdoc->next->prev = line->hdoc;
					line->hdoc = line->hdoc->next;
				}
				state |= WT_HDOC;
				state &= ~WT_SPACE;
				line->hdoc->head = i;
				line->hdoc->tail = i + 1;
			}
			else if (line->curr->buff[i] != ' ' && state & WT_HDOC)
				line->hdoc->tail++;
			else if (line->curr->buff[i] == ' ' &&  state & WT_HDOC)
			{
				state &= ~WT_HDOC;
				*(line->e_cmpl) |= HDOC;
			}
		}
		i++;
	}
	if (state & WT_HDOC || *(line->e_cmpl) > 0)
	{
		if (state & WT_HDOC)
			*(line->e_cmpl) |= HDOC;
		deal_prompt(line);
		deal_continue(line);
		while (line->hdoc && line->hdoc->next)
			line->hdoc = line->hdoc->next;
		while (buff->prev)
			buff = buff->prev;
		while (line->hdoc && line->hdoc->prev)
		{
			line->hdoc->cmd = expand_word(buff->buff, (t_token*)line->hdoc);
			line->hdoc = line->hdoc->prev;
		}
		if (line->hdoc)
			line->hdoc->cmd = expand_word(buff->buff, (t_token*)line->hdoc);
		return (1);
	}
	deal_prompt(line);
	return (0);
}

int		main(__attribute((unused)) int ac, __attribute((unused)) char **av, char **ep)
{
	t_line		*line;
	t_token		*tokens;
	t_command	*command;
	char		**env;
	char		*ret;

	env = collect_env(ep);
	line = get_struct();
	init_line(env, line);
	welcome(line);
	line->curr = ft_memalloc(sizeof(t_buff));
	line->beg_buff = line->curr;
	while (1)
	{
		put_prompt(line->prompt);
		check_path(line, env);
		deal_typing(line);
		write(1, "\n", 1);
		if (!deal_hdoc(line))
		{
				if (check_hdoc(line))
			continue;
		}
//		if (!deal_hdoc(line))
//			ft_putendl("YO");
		if (line->curr->buff[0] && line->tmp[0] != -1 && line->curr->buff[0] != 10)
		{
			ret = listnjoin(line);
			printf("line : [%s]\n", ret);
			*(line->e_cmpl) &= ~COMPLETION;
			save_history(line->index, line->curr->buff, &(line->hist), env);
			remove_line_continuation(line->curr->buff);
			// int i = 0;
			// int val[] = { BACKSLASH, DOUBLE_QUOTE, SINGLE_QUOTE, PARENTHESE, BRACKET, BACKQUOTE, };
			// for (size_t j=0;j<sizeof(val)/sizeof(*val);j++)
			// {
			// 	i |= val[j];
			// 	printf("i=%d\n"
			// 			"%-2d %-2d %-2d %-2d\n"
			// 			"%-2d %-2d %-2d %-2d\n"
			// 			"%-2d %-2d %-2d %-2d\n"
			// 			"%-2d %-2d %-2d %-2d\n"
			// 			"%-2d %-2d %-2d %-2d\n"
			// 			"%-2d %-2d %-2d %-2d\n",
			// 			i,
			// 			i & val[0], ~(i | ~val[0]), !(i & val[0]), i & ~val[0],
			// 			i & val[1], ~(i | ~val[1]), !(i & val[1]), i & ~val[1],
			// 			i & val[2], ~(i | ~val[2]), !(i & val[2]), i & ~val[2],
			// 			i & val[3], ~(i | ~val[3]), !(i & val[3]), i & ~val[3],
			// 			i & val[4], ~(i | ~val[4]), !(i & val[4]), i & ~val[4],
			// 			i & val[5], ~(i | ~val[5]), !(i & val[5]), i & ~val[5]
			// 			);
			// 	// i &= ~val[j];
			// }
			tokens = tokenise(line->curr->buff);
#ifdef DEBUG
			for (t_token *ptr = tokens; ptr; ptr = ptr->next) {
				printf("------------------------------\n"
						"type:%d spec:%d head:%ld tail:%ld\n",
						ptr->type, ptr->spec, ptr->head, ptr->tail);
				write(1, "buff: \"", 7);
				write(1, line->curr->buff + ptr->head, ptr->tail - ptr->head);
				write(1, "\" command: \"", 12);
				if (ptr->command)
					write(1, ptr->command, ft_strlen(ptr->command));
				write(1, "\"\n", 2);
				for (t_token *ptr2 = ptr->subs; ptr2; ptr2 = ptr2->next) {
					printf("------------------------------\n"
							"\ttype:%d spec:%d head:%ld tail:%ld\n",
							ptr2->type, ptr2->spec, ptr2->head, ptr2->tail);
					write(1, "\tsub: \"", 7);
					write(1, line->curr->buff + ptr2->head, ptr2->tail - ptr2->head);
					write(1, "\"\n", 2);
				}
			}
#endif
			(void)command;
			free_buff(line);
			del_all_state(line);
		}
	}
	return (0);
}
