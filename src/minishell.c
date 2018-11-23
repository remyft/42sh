/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 20:53:59 by rfontain          #+#    #+#             */
/*   Updated: 2018/11/23 06:37:10 by gbourgeo         ###   ########.fr       */
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

int		main(__unused int ac, __unused char **av, char **ep)
{
	t_line	*line;
	char	**env;

	env = collect_env(ep);
	line = init_line(env);
	while (1)
	{
		put_prompt(line->prompt);
		ft_bzero(line->buff, 8193);
		check_path(line, env);
		deal_typing(line);
		ft_putendl("");
		if (line->buff[0] && line->tmp[0] != -1 && line->buff[0] != 10)
		{
			*(line->e_cmpl) &= ~COMPLETION;
			save_history(line->index, line->buff, line->buff_tmp, &(line->curr), env);
			line->buff[line->len - 1] = '\n';
			// parse = NULL;
			// parse = ft_strsplit(line->buff, ';');
			// i = -1;
			// while (parse && parse[++i])
			// {
			// 	cmd = ft_strsplit_ws(parse[i]);
			// 	if (!(get_var(env, cmd)))
			// 		continue ;
			// 	deal_cmd(cmd, &env, &(line->save));
			// 	if (line->tree[1])
			// 		free_tree(line->tree[1]);
			// 	line->tree[1] = create_file_tree(getcwd(prompt, 4097));
			// 	if (line->tree[2])
			// 	{
			// 		free_tree(line->tree[2]);
			// 		line->tree[2] = NULL;
			// 	}
			// 	free_tab(&cmd);
			// }
			t_token *tokens = get_tokens(line->buff, 0);
			for (t_token *ptr = tokens; ptr; ptr = ptr->next) {
				printf("------------------------------\n"
						"type:%ld head:%ld tail:%ld quoted:%c\n",
						ptr->type, ptr->head, ptr->tail, ptr->quoted);
				write(1, "command: \"", 10);
				write(1, line->buff + ptr->head, ptr->tail - ptr->head);
				write(1, "\"\n", 2);
			}
			get_commands(tokens);
		}
	}
	return (0);
}
